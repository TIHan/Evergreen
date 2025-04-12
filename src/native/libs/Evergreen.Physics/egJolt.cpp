// When you are using pre-compiled headers, this source file is necessary for compilation to succeed.
// The Jolt headers don't include Jolt.h. Always include Jolt.h before including any other Jolt header.
// You can use Jolt.h in your precompiled header to speed up compilation.
#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Character/Character.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Collision/Shape/StaticCompoundShape.h>
#include <Jolt/Physics/Body/BodyLock.h>

// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>
#include <cassert>

#include "egJolt.h"

// Disable common warnings triggered by Jolt, you can use JPH_SUPPRESS_WARNING_PUSH / JPH_SUPPRESS_WARNING_POP to store and restore the warning state
JPH_SUPPRESS_WARNINGS

// All Jolt symbols are in the JPH namespace
using namespace JPH;

// If you want your code to compile using single or double precision write 0.0_r to get a Real value that compiles to double or float depending if JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;

// We're also using STL classes in this example
using namespace std;

inline EgJoltVector3 ConvertVector3(RVec3 v)
{
	EgJoltVector3 result = {};
	result.x = v.GetX();
	result.y = v.GetY();
	result.z = v.GetZ();
	return result;
}

inline RVec3 ConvertVector3(EgJoltVector3 v)
{
	return RVec3(v.x, v.y, v.z);
}

inline EgJoltVector4 ConvertVector4(Vec4 v)
{
	EgJoltVector4 result = {};
	result.x = v.GetX();
	result.y = v.GetY();
	result.z = v.GetZ();
	result.w = v.GetW();
	return result;
}

inline Vec4Arg ConvertVector4(EgJoltVector4 v)
{
	return Vec4Arg(v.x, v.y, v.z, v.w);
}

inline EgJoltQuaternion ConvertQuaternion(Quat q)
{
	EgJoltQuaternion result = {};
	result.x = q.GetX();
	result.y = q.GetY();
	result.z = q.GetZ();
	result.w = q.GetW();
	return result;
}

inline QuatArg ConvertQuaternion(EgJoltQuaternion q)
{
	return *(QuatArg*)&q;
}

inline BodyID ConvertBodyId(unsigned int bodyId)
{
	return *(BodyID const*)&bodyId;
}

// Callback for traces, connect this to your own trace function if you have one
static void TraceImpl(const char* inFMT, ...)
{
	// Format the message
	va_list list;
	va_start(list, inFMT);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), inFMT, list);
	va_end(list);

	// Print to the TTY
	cout << buffer << endl;
}

#ifdef JPH_ENABLE_ASSERTS

// Callback for asserts, connect this to your own assert handler if you have one
static bool AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, uint inLine)
{
	// Print to the TTY
	cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << endl;

	// Breakpoint
	return true;
};

#endif // JPH_ENABLE_ASSERTS

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
{
public:
	bool(*callbackShouldCollide)(unsigned char layer1, unsigned char layer2);

	virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
	{
		return callbackShouldCollide(inObject1, inObject2);
	}
};

// BroadPhaseLayerInterface implementation
// This defines a mapping between object and broadphase layers.
class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
{
public:
	unsigned char maxNumberOfLayers;

	virtual uint GetNumBroadPhaseLayers() const override
	{
		return maxNumberOfLayers;
	}

	virtual BroadPhaseLayer	GetBroadPhaseLayer(ObjectLayer inLayer) const override
	{
		JPH_ASSERT(inLayer < maxNumberOfLayers);
		return (BroadPhaseLayer)inLayer;
	}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
	virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
	{
		return "TODO: BroadPhaseLayerName";
	}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED
};

/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter
{
public:
	bool(*callbackShouldCollide)(unsigned char layer1, unsigned char layer2);

	virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override
	{
		return callbackShouldCollide(inLayer1, (unsigned char)inLayer2);
	}
};

class MyBodyFilter : public BodyFilter
{
};

class MyContactListener : public ContactListener
{
public:
	PhysicsSystem* physics;
	void(*callbackContactAdded)(EgJoltContactArgs);
	void(*callbackContactPersisted)(EgJoltContactArgs);

	virtual ValidateResult OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult) override
	{
		auto userData1 = inBody1.GetUserData();
		auto userData2 = inBody2.GetUserData();
		if (userData1 == userData2)
			return ValidateResult::RejectAllContactsForThisBodyPair;
		return ValidateResult::AcceptAllContactsForThisBodyPair;
	}

	virtual void OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
	{
		if (callbackContactAdded)
		{
			auto bodyId1 = inBody1.GetID();
			auto bodyId2 = inBody2.GetID();
			auto userData1 = inBody1.GetUserData();
			auto userData2 = inBody2.GetUserData();

			EgJoltContactArgs args;
			args.bodyId1 = *(unsigned int*)&bodyId1;
			args.userData1 = userData1;
			args.point1 = ConvertVector3(inManifold.GetWorldSpaceContactPointOn1(0));
			args.bodyId2 = *(unsigned int*)&bodyId2;
			args.userData2 = userData2;
			args.point2 = ConvertVector3(inManifold.GetWorldSpaceContactPointOn2(0));

			callbackContactAdded(args);
		}
	}

	virtual void OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
	{
		if (callbackContactPersisted)
		{
			auto bodyId1 = inBody1.GetID();
			auto bodyId2 = inBody2.GetID();
			auto userData1 = inBody1.GetUserData();
			auto userData2 = inBody2.GetUserData();

			EgJoltContactArgs args;
			args.bodyId1 = *(unsigned int*)&bodyId1;
			args.userData1 = userData1;
			args.point1 = ConvertVector3(inManifold.GetWorldSpaceContactPointOn1(0));
			args.bodyId2 = *(unsigned int*)&bodyId2;
			args.userData2 = userData2;
			args.point2 = ConvertVector3(inManifold.GetWorldSpaceContactPointOn2(0));

			callbackContactPersisted(args);
		}
	}

	virtual void OnContactRemoved(const SubShapeIDPair& inSubShapePair) override
	{
	}
};

class MyBodyActivationListener : public BodyActivationListener
{
public:
	virtual void OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) override
	{
	}

	virtual void OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) override
	{
	}
};

class MyCharacterVirtualContactListener : public CharacterContactListener
{
public:
	virtual void OnContactAdded(const CharacterVirtual* inCharacter, const BodyID& inBodyID2, const SubShapeID& inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings& ioSettings)
	{
	}
};

inline EActivation GetActivation(BodyInterface& bodyInterface, BodyID bodyId)
{
	if (bodyInterface.IsActive(bodyId))
	{
		return EActivation::Activate;
	}
	return EActivation::DontActivate;
}

// ------------------------------------

struct EgJoltInstanceInternal {
	TempAllocatorImpl* temp_allocator;
	JobSystemThreadPool* job_system;
	BPLayerInterfaceImpl* broad_phase_layer_interface;
	ObjectVsBroadPhaseLayerFilterImpl* object_vs_broadphase_layer_filter;
	ObjectLayerPairFilterImpl* object_vs_object_layer_filter;
	MyBodyActivationListener* body_activation_listener;
	MyContactListener* contact_listener;
	MyCharacterVirtualContactListener* characterContactListener;
	MyBodyFilter* bodyFilter;

	PhysicsSystem* physics_system;
};

inline void _Jolt_Body_SetVelocity(Body* body, Vec3Arg linearVelocity, Vec3Arg angularVelocity)
{
	if (!body->IsStatic())
	{
		body->SetLinearVelocityClamped(linearVelocity);
		body->SetAngularVelocityClamped(angularVelocity);
	}
}

inline EgJoltInstanceInternal* GetInternalInstance(EgJoltInstance instance)
{
	return (EgJoltInstanceInternal*)instance.internal;
}

inline BodyInterface& _egJolt_GetBodyInterfaceNoLock(EgJoltInstance instance)
{
	return GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();
}

inline const BodyLockInterfaceNoLock& _egJolt_GetBodyLockInterfaceNoLock(EgJoltInstance instance)
{
	return GetInternalInstance(instance)->physics_system->GetBodyLockInterfaceNoLock();
}

static inline Body* _egJolt_GetBody(EgJoltInstance instance, unsigned int bodyId)
{
	const BodyLockInterfaceNoLock& bodyInterface = _egJolt_GetBodyLockInterfaceNoLock(instance);
	Body*                          body          = bodyInterface.TryGetBody(ConvertBodyId(bodyId));
	assert(body != nullptr);
	return body;
}

inline bool _egJolt_Body_IsSensor(EgJoltInstance instance, unsigned int bodyId)
{
	return _egJolt_GetBody(instance, bodyId)->IsSensor();
}

inline void _egJolt_Body_SetIsSensor(EgJoltInstance instance, unsigned int bodyId, bool isSensor)
{
	_egJolt_GetBody(instance, bodyId)->SetIsSensor(isSensor);
}

inline void _egJolt_Body_SetPositionAndRotation(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position, EgJoltQuaternion rotation)
{
	_egJolt_GetBodyInterfaceNoLock(instance).SetPositionAndRotation(
		ConvertBodyId(bodyId),
		ConvertVector3(position),
		ConvertQuaternion(rotation),
		EActivation::DontActivate
	);
}

inline void _egJolt_Body_SetIsActive(EgJoltInstance instance, unsigned int bodyId, bool isActive)
{
	if (isActive)
	{
		_egJolt_GetBodyInterfaceNoLock(instance).ActivateBody(ConvertBodyId(bodyId));
	}
	else
	{
		_egJolt_GetBodyInterfaceNoLock(instance).DeactivateBody(ConvertBodyId(bodyId));
	}
}

inline unsigned int _egJoltAddBody(EgJoltInstance instance, EMotionType motionType, ObjectLayer layer, float mass, ShapeSettings::ShapeResult shapeResult, unsigned long long userData, BodyID* bodyId, EgJoltBodyState* state)
{
	BodyInterface& bodyInterface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();
	ShapeRefC shape = shapeResult.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

	EActivation activation = {};
	if (state->flags & EgJolt_BodyFlags_IsActive)
	{
		activation = EActivation::Activate;
	}
	else
	{
		activation = EActivation::DontActivate;
	}

	// Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
	BodyCreationSettings bodySettings(shape, ConvertVector3(state->position), *(Quat*)&state->rotation, motionType, layer);
	auto massProps = bodySettings.GetMassProperties();
	massProps.mMass = mass;
	bodySettings.mMassPropertiesOverride = massProps;
	bodySettings.mMotionQuality = EMotionQuality::LinearCast;
	bodySettings.mOverrideMassProperties = EOverrideMassProperties::CalculateInertia;
	bodySettings.mIsSensor = state->flags & EgJolt_BodyFlags_IsSensor;
	bodySettings.mLinearVelocity = ConvertVector3(state->linearVelocity);
	bodySettings.mAngularVelocity = ConvertVector3(state->angularVelocity);
	bodySettings.mAllowSleeping = true;
	bodySettings.mGravityFactor = state->gravityFactor;

	Body* body; // Note that if we run out of bodies this can return nullptr
	if (bodyId)
	{
		body = bodyInterface.CreateBodyWithID(*bodyId, bodySettings);
	}
	else
	{
		body = bodyInterface.CreateBody(bodySettings);
	}

	// Add it to the world
	bodyInterface.AddBody(body->GetID(), activation);
	bodyInterface.SetUserData(body->GetID(), userData);

	return *(unsigned int*)(&body->GetID());
}

inline unsigned int _egJoltAddBodyBox(EgJoltInstance instance, EgJoltVector3 scale, EMotionType motionType, ObjectLayer layer, float density, float mass, unsigned long long userData, BodyID* bodyId, EgJoltBodyState* state)
{
	BoxShapeSettings settings(Vec3(scale.x, scale.y, scale.z), 0);
	settings.mDensity = density;
	return _egJoltAddBody(instance, motionType, layer, mass, settings.Create(), userData, bodyId, state);
}

inline unsigned int _egJoltAddBodySphere(EgJoltInstance instance, float radius, EMotionType motionType, ObjectLayer layer, float density, float mass, unsigned long long userData, BodyID* bodyId, EgJoltBodyState* state)
{
	SphereShapeSettings settings(radius);
	settings.mDensity = density;
	return _egJoltAddBody(instance, motionType, layer, mass, settings.Create(), userData, bodyId, state);
}

inline unsigned int _egJoltAddBodyMesh(EgJoltInstance instance, EgJoltVector3* vertices, int vertexCount, unsigned int* indices, int indexCount, EMotionType motionType, ObjectLayer layer, float mass, unsigned long long userData, BodyID* bodyId, EgJoltBodyState* state)
{
	auto vertexListCount = vertexCount;
	auto vertexList = VertexList(vertexListCount);
	auto indexListCount = indexCount / 3;
	auto indexList = IndexedTriangleList(indexListCount);

	for (int i = 0; i < vertexListCount; i++)
	{
		auto v = vertices[i];
		vertexList[i] = Float3(v.x, v.y, v.z);
	}

	for (int i = 0; i < indexListCount; i++)
	{
		indexList[i] = IndexedTriangle(indices[i * 3], indices[i * 3 + 1], indices[i * 3 + 2]);
	}

	MeshShapeSettings settings(std::move(vertexList), std::move(indexList));
	return _egJoltAddBody(instance, motionType, layer, mass, settings.Create(), userData, bodyId, state);
}

inline unsigned int _egJoltAddStaticBodyCompoundMesh(EgJoltInstance instance, EgJoltCompoundMesh compoundMesh, EMotionType motionType, ObjectLayer layer, float mass, unsigned long long userData, BodyID* bodyId, EgJoltBodyState* state)
{
	Ref<StaticCompoundShapeSettings> compoundShapeSettings = new StaticCompoundShapeSettings;

	for (unsigned int k = 0; k < compoundMesh.meshCount; k++)
	{
		auto mesh = compoundMesh.meshes[k];
		auto vertexCount = mesh.vertexCount;
		auto vertices = mesh.vertices;
		auto indexCount = mesh.indexCount;
		auto indices = mesh.indices;

		auto vertexListCount = vertexCount;
		auto vertexList = VertexList(vertexListCount);
		auto indexListCount = indexCount / 3;
		auto indexList = IndexedTriangleList(indexListCount);

		for (unsigned int i = 0; i < vertexListCount; i++)
		{
			auto v = vertices[i];
			vertexList[i] = Float3(v.x, v.y, v.z);
		}

		for (unsigned int i = 0; i < indexListCount; i++)
		{
			indexList[i] = IndexedTriangle(indices[i * 3], indices[i * 3 + 1], indices[i * 3 + 2]);
		}

		MeshShapeSettings settings(std::move(vertexList), std::move(indexList));
		compoundShapeSettings->AddShape(Vec3Arg::sZero(), QuatArg::sIdentity(), settings.Create().Get());	
	}

	return _egJoltAddBody(instance, motionType, layer, mass, compoundShapeSettings->Create(), userData, bodyId, state);
}

CharacterVirtual* GetInternalCharacterVirtual(EgJoltCharacterVirtual egCharacter)
{
	return (CharacterVirtual*)egCharacter.internal;
}

Character* GetInternalCharacter(EgJoltCharacter egCharacter)
{
	return (Character*)egCharacter.internal;
}

inline EgJoltCharacterVirtual _egJoltCreateCharacterVirtual(EgJoltInstance instance, EgJoltCharacterSettings& settings, EgJoltVector3 position)
{
	auto internal = GetInternalInstance(instance);
	auto physics = internal->physics_system;

	//mStandingShape = RotatedTranslatedShapeSettings(Vec3(0, 0.5f * cCharacterHeightStanding + cCharacterRadiusStanding, 0), Quat::sIdentity(), new CapsuleShape(0.5f * cCharacterHeightStanding, cCharacterRadiusStanding)).Create().Get();
	auto rot = Quat::sRotation(Vec3::sAxisX(), DegreesToRadians(90));
	Ref<Shape> standingShape = RotatedTranslatedShapeSettings(Vec3(0, 0, 0.5f * settings.standingHeight + settings.standingRadius), rot, new CapsuleShape(0.5f * settings.standingHeight, settings.standingRadius)).Create().Get();

	Ref<CharacterVirtualSettings> virtualSettings = new CharacterVirtualSettings();
	virtualSettings->mMaxSlopeAngle = settings.maxSlopeAngle;
	virtualSettings->mMaxStrength = settings.maxStrength;
	virtualSettings->mShape = standingShape;
	virtualSettings->mBackFaceMode = EBackFaceMode::IgnoreBackFaces;
	virtualSettings->mCharacterPadding = settings.padding;
	virtualSettings->mPenetrationRecoverySpeed = settings.penetrationRecoverySpeed;
	virtualSettings->mPredictiveContactDistance = settings.predictiveContactDistance;
	virtualSettings->mSupportingVolume = Plane(Vec3::sAxisZ(), -settings.standingRadius); // Accept contacts that touch the lower sphere of the capsule
	virtualSettings->mUp = Vec3::sAxisZ();
	virtualSettings->mMass = settings.mass;
	virtualSettings->mInnerBodyLayer = settings.layer;

	auto jCharacterVirtual = new CharacterVirtual(virtualSettings, ConvertVector3(position), Quat::sIdentity(), physics);
	jCharacterVirtual->SetListener(internal->characterContactListener);

	EgJoltCharacterVirtual character = {};
	character.internal = jCharacterVirtual;
	return character;
}

inline EgJoltCharacter _egJoltCreateCharacter(EgJoltInstance instance, EgJoltCharacterSettings& settings, EgJoltVector3 position, ObjectLayer layer, unsigned long long userData)
{
	auto internal = GetInternalInstance(instance);
	auto physics = internal->physics_system;

	auto rot = Quat::sRotation(Vec3::sAxisX(), DegreesToRadians(90));
	Ref<Shape> standingShape = RotatedTranslatedShapeSettings(Vec3(0, 0, 0.5f * settings.standingHeight + settings.standingRadius), rot, new CapsuleShape(0.5f * settings.standingHeight, settings.standingRadius)).Create().Get();

	Ref<CharacterSettings> jSettings = new CharacterSettings();
	jSettings->mMass = settings.mass;
	jSettings->mMaxSlopeAngle = settings.maxSlopeAngle;
	jSettings->mShape = standingShape;
	jSettings->mLayer = layer;
	jSettings->mUp = Vec3::sAxisZ();
	jSettings->mSupportingVolume = Plane(Vec3::sAxisZ(), -settings.standingRadius); // Accept contacts that touch the lower sphere of the capsule

	auto jCharacter = new Character(jSettings, ConvertVector3(position), Quat::sIdentity(), userData, physics);
	jCharacter->AddToPhysicsSystem(EActivation::Activate);

	EgJoltCharacter character = {};
	character.internal = jCharacter;
	return character;
}

extern "C" {

	EG_EXPORT unsigned int egJoltGetMaxBodies()
	{
		// This is the max amount of rigid bodies that you can add to the physics system. If you try to add more you'll get an error.
		// Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
		return 65536;
	}

	EG_EXPORT unsigned int egJoltGetMaxBodyPairs()
	{
		// This is the max amount of body pairs that can be queued at any time (the broad phase will detect overlapping
		// body pairs based on their bounding boxes and will insert them into a queue for the narrowphase). If you make this buffer
		// too small the queue will fill up and the broad phase jobs will start to do narrow phase work. This is slightly less efficient.
		// Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
		return 65536;
	}

	EG_EXPORT unsigned int egJoltGetMaxContactConstraints()
	{
		// This is the maximum size of the contact constraint buffer. If more contacts (collisions between bodies) are detected than this
		// number then these contacts will be ignored and bodies will start interpenetrating / fall through the world.
		// Note: This value is low because this is a simple test. For a real project use something in the order of 10240.
		return 10240;
	}

	EG_EXPORT void egJoltSharedInit()
	{
		// Register allocation hook
		RegisterDefaultAllocator();

		// Install callbacks
		Trace = TraceImpl;
		JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

		// Create a factory
		Factory::sInstance = new Factory();

		// Register all Jolt physics types
		RegisterTypes();
	}

	EG_EXPORT void egJoltSharedDestroy()
	{
		// Unregisters all types with the factory and cleans up the default material
		UnregisterTypes();

		// Destroy the factory
		delete Factory::sInstance;
		Factory::sInstance = nullptr;
	}

	EG_EXPORT EgJoltInstance egJoltCreateInstance(
		unsigned char maxNumberOfLayers,
		void(*callbackContactAdded)(EgJoltContactArgs), 
		void(*callbackContactPersisted)(EgJoltContactArgs),
		bool(*callbackShouldCollide)(unsigned char layer1, unsigned char layer2)
	)
	{
		// We need a temp allocator for temporary allocations during the physics update. We're
		// pre-allocating 10 MB to avoid having to do allocations during the physics update.
		// B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
		// If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
		// malloc / free.
		TempAllocatorImpl* temp_allocator = new TempAllocatorImpl(10 * 1024 * 1024);

		// We need a job system that will execute physics jobs on multiple threads. Typically
		// you would implement the JobSystem interface yourself and let Jolt Physics run on top
		// of your own job scheduler. JobSystemThreadPool is an example implementation.
		JobSystemThreadPool* job_system = new JobSystemThreadPool(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);

		const uint cMaxBodies = egJoltGetMaxBodies();
		// This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
		const uint cNumBodyMutexes = 0;
		const uint cMaxBodyPairs = egJoltGetMaxBodyPairs();
		const uint cMaxContactConstraints = egJoltGetMaxContactConstraints();

		// Create mapping table from object layer to broadphase layer
		// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
		BPLayerInterfaceImpl* broad_phase_layer_interface = new BPLayerInterfaceImpl();
		broad_phase_layer_interface->maxNumberOfLayers = maxNumberOfLayers;

		// Create class that filters object vs broadphase layers
		// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
		ObjectVsBroadPhaseLayerFilterImpl* object_vs_broadphase_layer_filter = new ObjectVsBroadPhaseLayerFilterImpl();
		object_vs_broadphase_layer_filter->callbackShouldCollide = callbackShouldCollide;

		// Create class that filters object vs object layers
		// Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
		ObjectLayerPairFilterImpl* object_vs_object_layer_filter = new ObjectLayerPairFilterImpl();
		object_vs_object_layer_filter->callbackShouldCollide = callbackShouldCollide;

		// Now we can create the actual physics system.
		PhysicsSystem* physics_system = new PhysicsSystem();
		physics_system->Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, *broad_phase_layer_interface, *object_vs_broadphase_layer_filter, *object_vs_object_layer_filter);
		auto settings = physics_system->GetPhysicsSettings();
		settings.mDeterministicSimulation = true;
		physics_system->SetPhysicsSettings(settings);

		// A body activation listener gets notified when bodies activate and go to sleep
		// Note that this is called from a job so whatever you do here needs to be thread safe.
		// Registering one is entirely optional.
		MyBodyActivationListener* body_activation_listener = new MyBodyActivationListener();
		physics_system->SetBodyActivationListener(body_activation_listener);

		// A contact listener gets notified when bodies (are about to) collide, and when they separate again.
		// Note that this is called from a job so whatever you do here needs to be thread safe.
		// Registering one is entirely optional.
		MyContactListener* contact_listener = new MyContactListener();

		// REVIEW: This is odd isn't it? Why are we calling these here?
		//         Well let me tell you a story.
		//         Since these callbacks can be called into managed code,
		//         there is a bug in NET9 where competing threads trying to
		//         JIT one of these callbacks from multiple threads spawned by C++
		//         incorrectly handles exceptions from C++ and the process immediately dies.
		//for (int i = 0; i < 100; i++)
		//{
		//	callbackContactAdded(EgJoltContactArgs());
		//	callbackContactPersisted(EgJoltContactArgs());
		//}
		contact_listener->callbackContactAdded = callbackContactAdded;
		contact_listener->callbackContactPersisted = callbackContactPersisted;
		contact_listener->physics = physics_system;
		physics_system->SetContactListener(contact_listener);

		auto characterContactListener = new MyCharacterVirtualContactListener();

		auto internalInstance = new EgJoltInstanceInternal();
		internalInstance->temp_allocator = temp_allocator;
		internalInstance->job_system = job_system;
		internalInstance->broad_phase_layer_interface = broad_phase_layer_interface;
		internalInstance->object_vs_broadphase_layer_filter = object_vs_broadphase_layer_filter;
		internalInstance->object_vs_object_layer_filter = object_vs_object_layer_filter;
		internalInstance->physics_system = physics_system;
		internalInstance->body_activation_listener = body_activation_listener;
		internalInstance->contact_listener = contact_listener;
		internalInstance->characterContactListener = characterContactListener;
		internalInstance->bodyFilter = new MyBodyFilter();

		Vec3Arg gravity = {};
		physics_system->SetGravity(gravity);

		EgJoltInstance instance = {};
		instance.internal = internalInstance;
		return instance;
	}

	EG_EXPORT void egJoltDestroyInstance(EgJoltInstance instance)
	{
		auto internalInstance = GetInternalInstance(instance);

		delete internalInstance->temp_allocator;
		delete internalInstance->job_system;
		delete internalInstance->broad_phase_layer_interface;
		delete internalInstance->object_vs_broadphase_layer_filter;
		delete internalInstance->object_vs_object_layer_filter;
		delete internalInstance->physics_system;
		delete internalInstance->body_activation_listener;
		delete internalInstance->contact_listener;
		delete internalInstance->characterContactListener;
		delete internalInstance->bodyFilter;
		delete internalInstance;
	}

	// If you take larger steps than 1 / 60th of a second you need to do multiple collision steps in order to keep the simulation stable. Do 1 collision step per 1 / 60th of a second (round up).
	EG_EXPORT void egJoltUpdate(EgJoltInstance instance, float deltaTime, int collisionSteps)
	{
		auto internalInstance = GetInternalInstance(instance);

		// Step the world
		internalInstance->physics_system->Update(deltaTime, collisionSteps, internalInstance->temp_allocator, internalInstance->job_system);
	}

	EG_EXPORT void egJoltSetGravity(EgJoltInstance instance, EgJoltVector3 gravity)
	{
		GetInternalInstance(instance)->physics_system->SetGravity(Vec3Arg(gravity.x, gravity.y, gravity.z));
	}

	EG_EXPORT void egJoltOptimizeBroadPhase(EgJoltInstance instance)
	{
		GetInternalInstance(instance)->physics_system->OptimizeBroadPhase();
	}

	EG_EXPORT unsigned int egJoltGetCharacterBodyId(EgJoltInstance instance, EgJoltCharacter character)
	{
		auto jCharacter = GetInternalCharacter(character);
		auto bodyID = jCharacter->GetBodyID();
		return *(unsigned int*)&bodyID;
	}

	EG_EXPORT bool egJoltAreBodiesColliding(EgJoltInstance instance, unsigned int bodyId1, unsigned int bodyId2)
	{
		auto physicsSystem = GetInternalInstance(instance)->physics_system;
		auto& bodyInterface = physicsSystem->GetBodyInterfaceNoLock();

		auto shape = bodyInterface.GetShape(ConvertBodyId(bodyId1));
		auto bodyID1 = ConvertBodyId(bodyId1);
		auto bodyID2 = ConvertBodyId(bodyId2);

		// Settings
		CollideShapeSettings settings;
		settings.mActiveEdgeMode = EActiveEdgeMode::CollideWithAll;
		settings.mBackFaceMode = EBackFaceMode::IgnoreBackFaces;

		AllHitCollisionCollector<CollideShapeCollector> collector;
		physicsSystem->GetNarrowPhaseQuery().CollideShape(shape, Vec3::sReplicate(1.0f), bodyInterface.GetCenterOfMassTransform(bodyID1), settings, RVec3::sZero(), collector);
		if (collector.HadHit())
		{
			auto count = collector.mHits.size();
			for (int i = 0; i < count; i++)
			{
				if (collector.mHits[i].mBodyID2 == bodyID2)
				{
					return true;
				}
			}

			return false;
		}
		else
		{
			return false;
		}
	}

	EG_EXPORT void egJolt_Body_InvalidateContactCache(EgJoltInstance instance, unsigned int bodyId)
	{
		GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock().InvalidateContactCache(ConvertBodyId(bodyId));
	}

	EG_EXPORT void egJoltBodySetGravityFactor(EgJoltInstance instance, unsigned int bodyId, float gravityFactor)
	{
		GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock().SetGravityFactor(ConvertBodyId(bodyId), gravityFactor);
	}

	EG_EXPORT unsigned int egJoltAddBodyDynamicBox(EgJoltInstance instance, EgJoltVector3 scale, float density, float mass, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state)
	{
		return _egJoltAddBodyBox(instance, scale, EMotionType::Dynamic, state->layer, density, mass, userData, (BodyID*)bodyId, state);
	}

	EG_EXPORT unsigned int egJoltAddBodyDynamicSphere(EgJoltInstance instance, float radius, float density, float mass, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state)
	{
		return _egJoltAddBodySphere(instance, radius, EMotionType::Dynamic, state->layer, density, mass, userData, (BodyID*)bodyId, state);
	}

	EG_EXPORT unsigned int egJoltAddBodyStaticBox(EgJoltInstance instance, EgJoltVector3 scale, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state)
	{
		return _egJoltAddBodyBox(instance,  scale, EMotionType::Static, state->layer, 0, 0, userData, (BodyID*)bodyId, state);
	}

	EG_EXPORT unsigned int egJoltAddBodyStaticMesh(EgJoltInstance instance, EgJoltVector3* vertices, int vertexCount, unsigned int* indices, int indexCount, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state)
	{
		return _egJoltAddBodyMesh(instance, vertices, vertexCount, indices, indexCount, EMotionType::Static, state->layer, 0, userData, (BodyID*)bodyId, state);
	}

	EG_EXPORT unsigned int egJoltAddBodyStaticCompoundMesh(EgJoltInstance instance, EgJoltCompoundMesh compoundMesh, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state)
	{
		return _egJoltAddStaticBodyCompoundMesh(instance, compoundMesh, EMotionType::Static, state->layer, 0, userData, (BodyID*)bodyId, state);
	}

	EG_EXPORT unsigned long long egJoltGetBodyUserData(EgJoltInstance instance, unsigned int bodyId)
	{
		BodyInterface& bodyInterface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();
		return bodyInterface.GetUserData(*(BodyID*)&bodyId);
	}

	EG_EXPORT void egJoltSetBodyUserData(EgJoltInstance instance, unsigned int bodyId, unsigned long long userData)
	{
		BodyInterface& bodyInterface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();
		bodyInterface.SetUserData(*(BodyID*)&bodyId, userData);
	}

	EG_EXPORT void egJoltActivateBody(EgJoltInstance instance, unsigned int bodyId)
	{
		BodyInterface& bodyInterface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();
		bodyInterface.ActivateBody(*(BodyID*)&bodyId);
	}

	EG_EXPORT void egJoltDeactivateBody(EgJoltInstance instance, unsigned int bodyId)
	{
		BodyInterface& bodyInterface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();
		bodyInterface.DeactivateBody(*(BodyID*)&bodyId);
	}

	EG_EXPORT void egJoltRemoveBody(EgJoltInstance instance, unsigned int bodyId)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		body_interface.RemoveBody(*(BodyID*)&bodyId);
		body_interface.DestroyBody(*(BodyID*)&bodyId);
	}

	EG_EXPORT bool egJoltIsBodyActive(EgJoltInstance instance, unsigned int bodyId)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		return body_interface.IsActive(*(BodyID*)&bodyId);
	}

	EG_EXPORT void egJoltAddBodyImpulse(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 impulse)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		body_interface.AddImpulse(ConvertBodyId(bodyId), RVec3Arg(impulse.x, impulse.y, impulse.z));
	}

	EG_EXPORT void egJoltAddBodyAngularImpulse(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 angularImpulse)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		body_interface.AddAngularImpulse(ConvertBodyId(bodyId), RVec3Arg(angularImpulse.x, angularImpulse.y, angularImpulse.z));
	}

	EG_EXPORT void egJoltSetBodyPosition(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		body_interface.SetPosition(ConvertBodyId(bodyId), RVec3Arg(position.x, position.y, position.z), GetActivation(body_interface, ConvertBodyId(bodyId)));
	}

	EG_EXPORT void egJoltSetBodyPositionAndRotationAndVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position, EgJoltQuaternion rotation, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		if (body_interface.IsActive(ConvertBodyId(bodyId)))
		{
			body_interface.SetPositionRotationAndVelocity(ConvertBodyId(bodyId), ConvertVector3(position), *(Quat*)&rotation, ConvertVector3(linearVelocity), ConvertVector3(angularVelocity));
		}
		else
		{
			body_interface.SetPositionAndRotation(ConvertBodyId(bodyId), ConvertVector3(position), *(Quat*)&rotation, EActivation::DontActivate);
		}
	}

	EG_EXPORT void egJoltSetBodyPositionAndVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		body_interface.SetPosition(ConvertBodyId(bodyId), RVec3Arg(position.x, position.y, position.z), GetActivation(body_interface, ConvertBodyId(bodyId)));

		if (body_interface.IsActive(ConvertBodyId(bodyId)))
		{
			body_interface.SetLinearAndAngularVelocity(ConvertBodyId(bodyId), ConvertVector3(linearVelocity), ConvertVector3(angularVelocity));
		}
	}

	EG_EXPORT void egJoltSetBodyVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		if (body_interface.IsActive(ConvertBodyId(bodyId)))
		{
			body_interface.SetLinearAndAngularVelocity(ConvertBodyId(bodyId), ConvertVector3(linearVelocity), ConvertVector3(angularVelocity));
		}
	}

	EG_EXPORT void egJoltSetBodyVelocityAndActivate(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		body_interface.SetLinearAndAngularVelocity(ConvertBodyId(bodyId), ConvertVector3(linearVelocity), ConvertVector3(angularVelocity));
	}

	EG_EXPORT EgJoltVector3 egJoltGetBodyPosition(EgJoltInstance instance, unsigned int bodyId)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		return ConvertVector3(body_interface.GetPosition(ConvertBodyId(bodyId)));
	}

	EG_EXPORT void egJoltSetBodyPositionAndRotation(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position, EgJoltQuaternion rotation)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		body_interface.SetPositionAndRotation(ConvertBodyId(bodyId), RVec3Arg(position.x, position.y, position.z), QuatArg(rotation.x, rotation.y, rotation.z, rotation.w), GetActivation(body_interface, ConvertBodyId(bodyId)));
	}

	EG_EXPORT void egJoltGetBodyPositionAndRotation(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& position, EgJoltQuaternion& rotation)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		RVec3 _position = {};
		Quat _rotation = {};

		body_interface.GetPositionAndRotation(ConvertBodyId(bodyId), _position, _rotation);

		position.x = _position.GetX();
		position.y = _position.GetY();
		position.z = _position.GetZ();

		rotation.x = _rotation.GetX();
		rotation.y = _rotation.GetY();
		rotation.z = _rotation.GetZ();
		rotation.w = _rotation.GetW();
	}

	EG_EXPORT void egJoltGetBodyCenterOfMassPositionAndRotation(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& position, EgJoltQuaternion& rotation)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		RVec3 _position = body_interface.GetCenterOfMassPosition(*(BodyID const*)&bodyId);
		Quat _rotation = body_interface.GetRotation(*(BodyID const*)&bodyId);

		position.x = _position.GetX();
		position.y = _position.GetY();
		position.z = _position.GetZ();

		rotation.x = _rotation.GetX();
		rotation.y = _rotation.GetY();
		rotation.z = _rotation.GetZ();
		rotation.w = _rotation.GetW();
	}

	EG_EXPORT void egJoltGetBodyVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& linearVelocity, EgJoltVector3& angularVelocity)
	{
		BodyInterface& body_interface = GetInternalInstance(instance)->physics_system->GetBodyInterfaceNoLock();

		RVec3 _linearVelocity = {};
		RVec3 _angularVelocity = {};

		body_interface.GetLinearAndAngularVelocity(*(BodyID const*)&bodyId, _linearVelocity, _angularVelocity);

		linearVelocity.x = _linearVelocity.GetX();
		linearVelocity.y = _linearVelocity.GetY();
		linearVelocity.z = _linearVelocity.GetZ();

		angularVelocity.x = _angularVelocity.GetX();
		angularVelocity.y = _angularVelocity.GetY();
		angularVelocity.z = _angularVelocity.GetZ();
	}

	EG_EXPORT void egJoltGetBodyCenterOfMassPositionAndRotationAndVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& position, EgJoltQuaternion& rotation, EgJoltVector3& linearVelocity, EgJoltVector3& angularVelocity)
	{
		egJoltGetBodyCenterOfMassPositionAndRotation(instance, bodyId, position, rotation);
		egJoltGetBodyVelocity(instance, bodyId, linearVelocity, angularVelocity);
	}

	/* CHARACTER VIRTUAL */

	EG_EXPORT EgJoltCharacterVirtual egJoltCreateCharacterVirtual(EgJoltInstance instance, EgJoltCharacterSettings& settings, EgJoltVector3 position)
	{
		return _egJoltCreateCharacterVirtual(instance, settings, position);
	}

	EG_EXPORT void egJoltDestroyCharacterVirtual(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		delete character.internal;
		character.internal = nullptr;
	}

	EG_EXPORT void egJoltGetCharacterVirtualWorldTransform(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltMatrix4x4& transform)
	{
		auto characterInternal = GetInternalCharacterVirtual(character);

		auto _transform = characterInternal->GetWorldTransform();

		transform.m0 = ConvertVector4(_transform.GetColumn4(0));
		transform.m1 = ConvertVector4(_transform.GetColumn4(1));
		transform.m2 = ConvertVector4(_transform.GetColumn4(2));
		transform.m3 = ConvertVector4(_transform.GetColumn4(3));
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualCenterOfMassPosition(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		return ConvertVector3(GetInternalCharacterVirtual(character)->GetCenterOfMassTransform().GetTranslation());
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualPosition(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		return ConvertVector3(GetInternalCharacterVirtual(character)->GetPosition());
	}

	EG_EXPORT void egJolt_CharacterVirtual_SetPosition(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltVector3 position)
	{
		auto characterVirtual = GetInternalCharacterVirtual(character);
		characterVirtual->SetPosition(ConvertVector3(position));
	}

	EG_EXPORT void egJolt_CharacterVirtual_RefreshContacts(EgJoltInstance instance, EgJoltCharacterVirtual character, unsigned char layer)
	{
		auto internalInstance = GetInternalInstance(instance);
		auto physics = internalInstance->physics_system;

		auto characterVirtual = GetInternalCharacterVirtual(character);

		characterVirtual->RefreshContacts(
			physics->GetDefaultBroadPhaseLayerFilter(layer),
			physics->GetDefaultLayerFilter(layer),
			(*internalInstance->bodyFilter),
			{ },
			*internalInstance->temp_allocator
		);
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualLinearVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		return ConvertVector3(GetInternalCharacterVirtual(character)->GetLinearVelocity());
	}

	EG_EXPORT void egJoltSetCharacterVirtualLinearVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltVector3 linearVelocity)
	{
		GetInternalCharacterVirtual(character)->SetLinearVelocity(ConvertVector3(linearVelocity));
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualGroundVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		return ConvertVector3(GetInternalCharacterVirtual(character)->GetGroundVelocity());
	}

	EG_EXPORT void egJoltUpdateCharacterVirtualGroundVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		GetInternalCharacterVirtual(character)->UpdateGroundVelocity();
	}

	EG_EXPORT EgJolt_GroundState egJolt_CharacterVirtual_GetGroundState(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		switch (GetInternalCharacterVirtual(character)->GetGroundState())
		{
			case CharacterVirtual::EGroundState::OnGround:
				return EgJolt_GroundState::OnGround;

			case CharacterVirtual::EGroundState::InAir:
				return EgJolt_GroundState::InAir;

			case CharacterVirtual::EGroundState::OnSteepGround:
				return EgJolt_GroundState::OnSteepGround;

			default:
				break;
		}

		return EgJolt_GroundState::NotSupported;
	}

	EG_EXPORT bool egJoltIsCharacterVirtualOnSlopeTooSteep(EgJoltInstance instance, EgJoltCharacterVirtual character)
	{
		auto c = GetInternalCharacterVirtual(character);
		return c->IsSlopeTooSteep(c->GetGroundNormal());
	}

	EG_EXPORT void egJolt_CharacterVirtual_SetRotation(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltQuaternion rotation)
	{
		auto c = GetInternalCharacterVirtual(character);
		c->SetRotation(*(Quat*)&rotation);
	}

	EG_EXPORT void egJolt_CharacterVirtual_SetUp(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltVector3 up)
	{
		auto c = GetInternalCharacterVirtual(character);
		c->SetUp(ConvertVector3(up));
	}

	EG_EXPORT void egJoltUpdateCharacterVirtual(EgJoltInstance instance, EgJoltCharacterVirtual character, float deltaTime, EgJoltCharacterVirtualUpdateSettings& updateSettings)
	{
		auto internalInstance = GetInternalInstance(instance);
		auto characterVirtual = GetInternalCharacterVirtual(character);

		auto physics = internalInstance->physics_system;

		CharacterVirtual::ExtendedUpdateSettings settings;
		settings.mStickToFloorStepDown = ConvertVector3(updateSettings.stickToFloorStepDown);
		settings.mWalkStairsStepUp = ConvertVector3(updateSettings.walkStairsStepUp);
		settings.mWalkStairsCosAngleForwardContact = updateSettings.walkStairsCosAngleForwardContact;
		settings.mWalkStairsStepDownExtra = ConvertVector3(updateSettings.walkStairsStepDownExtra);
		settings.mWalkStairsStepForwardTest = updateSettings.walkStairsStepForwardTest;
		settings.mWalkStairsMinStepForward = updateSettings.walkStairsMinStepForward;

		characterVirtual->ExtendedUpdate(
			deltaTime,
			-characterVirtual->GetUp() * physics->GetGravity().Length(),
			settings,
			physics->GetDefaultBroadPhaseLayerFilter(updateSettings.layer),
			physics->GetDefaultLayerFilter(updateSettings.layer),
			(*internalInstance->bodyFilter),
			{ },
			*internalInstance->temp_allocator
		);
	}

	EG_EXPORT void egJoltGetCharacterVirtualActiveDynamicContacts(EgJoltInstance instance, EgJoltCharacterVirtual character, void(*callbackContact)(unsigned int))
	{
		auto internalInstance = GetInternalInstance(instance);
		auto physics = internalInstance->physics_system;
		auto characterVirtual = GetInternalCharacterVirtual(character);

		auto contacts = characterVirtual->GetActiveContacts();

		for (auto i = 0; i < contacts.size(); i++)
		{
			auto contact = contacts[i];
			auto bodyId = contact.mBodyB;
			if (contact.mMotionTypeB == EMotionType::Dynamic)
			{
				callbackContact(*(unsigned int*)&bodyId);
			}
		}
	}

	/* CHARACTER */

	EG_EXPORT EgJoltCharacter egJoltCreateCharacter(EgJoltInstance instance, EgJoltCharacterSettings& settings, EgJoltVector3 position, unsigned long long userData)
	{
		return _egJoltCreateCharacter(instance, settings, position, settings.layer, userData);
	}

	EG_EXPORT void egJoltDestroyCharacter(EgJoltInstance instance, EgJoltCharacter character)
	{
		GetInternalCharacter(character)->RemoveFromPhysicsSystem();
		delete character.internal;
	}

	EG_EXPORT void egJoltGetCharacterWorldTransform(EgJoltInstance instance, EgJoltCharacter character, EgJoltMatrix4x4& transform)
	{
		auto jCharacter = GetInternalCharacter(character);

		auto _transform = jCharacter->GetWorldTransform();

		transform.m0 = ConvertVector4(_transform.GetColumn4(0));
		transform.m1 = ConvertVector4(_transform.GetColumn4(1));
		transform.m2 = ConvertVector4(_transform.GetColumn4(2));
		transform.m3 = ConvertVector4(_transform.GetColumn4(3));
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterCenterOfMassPosition(EgJoltInstance instance, EgJoltCharacter character)
	{
		return ConvertVector3(GetInternalCharacter(character)->GetCenterOfMassPosition());
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterPosition(EgJoltInstance instance, EgJoltCharacter character)
	{
		return ConvertVector3(GetInternalCharacter(character)->GetPosition());
	}

	EG_EXPORT void egJoltSetCharacterPosition(EgJoltInstance instance, EgJoltCharacter character, EgJoltVector3 position)
	{
		GetInternalCharacter(character)->SetPosition(ConvertVector3(position));
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterLinearVelocity(EgJoltInstance instance, EgJoltCharacter character)
	{
		return ConvertVector3(GetInternalCharacter(character)->GetLinearVelocity());
	}

	EG_EXPORT void egJoltSetCharacterLinearVelocity(EgJoltInstance instance, EgJoltCharacter character, EgJoltVector3 linearVelocity)
	{
		GetInternalCharacter(character)->SetLinearVelocity(ConvertVector3(linearVelocity));
	}

	EG_EXPORT EgJoltVector3 egJoltGetCharacterGroundVelocity(EgJoltInstance instance, EgJoltCharacter character)
	{
		return ConvertVector3(GetInternalCharacter(character)->GetGroundVelocity());
	}

	EG_EXPORT bool egJoltIsCharacterOnGround(EgJoltInstance instance, EgJoltCharacter character)
	{
		return GetInternalCharacter(character)->GetGroundState() == CharacterVirtual::EGroundState::OnGround;
	}

	EG_EXPORT void egJoltPostUpdateCharacter(EgJoltInstance instance, EgJoltCharacter character, float maxSeparationDistance)
	{
		GetInternalCharacter(character)->PostSimulation(maxSeparationDistance);
	}

	EG_EXPORT void egJolt_Body_GetState(const EgJoltInstance instance, const unsigned int bodyId, EgJoltBodyState* outState)
	{
		const Body* body = _egJolt_GetBody(instance, bodyId);

		outState->position        = ConvertVector3(body->GetPosition());
		outState->rotation        = ConvertQuaternion(body->GetRotation());
		outState->linearVelocity  = ConvertVector3(body->GetLinearVelocity());
		outState->angularVelocity = ConvertVector3(body->GetAngularVelocity());

		EgJolt_BodyFlags flags = EgJolt_BodyFlags_None;

		if (body->IsSensor())
		{
			flags = flags | EgJolt_BodyFlags_IsSensor;
		}

		if (body->IsActive())
		{
			flags = flags | EgJolt_BodyFlags_IsActive;
		}

		outState->flags = flags;
		outState->layer = body->GetObjectLayer();
	}

	EG_EXPORT void egJolt_Body_SetState(const EgJoltInstance instance, unsigned int bodyId, const EgJoltBodyState* state)
	{
		Body* body = _egJolt_GetBody(instance, bodyId);

		_egJolt_Body_SetPositionAndRotation(instance, bodyId, state->position, state->rotation);

		_Jolt_Body_SetVelocity(body, ConvertVector3(state->linearVelocity), ConvertVector3(state->angularVelocity));

		bool isSensor = state->flags & EgJolt_BodyFlags_IsSensor;
		if (body->IsSensor() != isSensor)
		{
			body->SetIsSensor(isSensor);
		}

		bool isActive = state->flags & EgJolt_BodyFlags_IsActive;
		if (body->IsActive() != isActive)
		{
			_egJolt_Body_SetIsActive(instance, bodyId, isActive);
		}

		unsigned char layer = body->GetObjectLayer();
		if (layer != state->layer)
		{
			_egJolt_GetBodyInterfaceNoLock(instance).SetObjectLayer(ConvertBodyId(bodyId), state->layer);
		}
	}

	EG_EXPORT int egJolt_Vector3_IsNearZero(EgJoltVector3 v)
	{
		return ConvertVector3(v).IsNearZero();
	}

	EG_EXPORT EgJoltQuaternion egJolt_Quaternion_Normalize(EgJoltQuaternion q)
	{
		return ConvertQuaternion(ConvertQuaternion(q).Normalized());
	}

	EG_EXPORT int egJolt_Quaternion_IsNormalized(EgJoltQuaternion q)
	{
		return ConvertQuaternion(q).IsNormalized();
	}
}