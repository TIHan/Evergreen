#pragma once

#define EG_EXPORT __declspec(dllexport)

typedef struct {
	void* internal;
} EgJoltInstance;

typedef struct {
	float x;
	float y;
	float z;
} EgJoltVector3;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} EgJoltVector4;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} EgJoltQuaternion;

typedef struct {
	EgJoltVector4 m0;
	EgJoltVector4 m1;
	EgJoltVector4 m2;
	EgJoltVector4 m3;
} EgJoltMatrix4x4;

enum EgJolt_BodyFlags : unsigned char
{
	EgJolt_BodyFlags_None,
	EgJolt_BodyFlags_IsActive,
	EgJolt_BodyFlags_IsSensor
};

inline EgJolt_BodyFlags operator|(EgJolt_BodyFlags a, EgJolt_BodyFlags b)
{
	return static_cast<EgJolt_BodyFlags>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}

typedef struct {
	float maxSlopeAngle;
	float maxStrength;
	float padding;
	float penetrationRecoverySpeed;
	float predictiveContactDistance;
	float standingHeight;
	float standingRadius;
	float crouchingHeight;
	float crouchingRadius;
	float mass;
	unsigned char layer;
} EgJoltCharacterSettings;

typedef struct {
	void* internal;
} EgJoltCharacterVirtual;

typedef struct {
	void* internal;
} EgJoltCharacter;

typedef struct {
	unsigned int bodyId1;
	unsigned long long userData1;
	EgJoltVector3 point1;
	unsigned int bodyId2;
	unsigned long long userData2;
	EgJoltVector3 point2;
} EgJoltContactArgs;

typedef struct {
	unsigned int vertexCount;
	EgJoltVector3* vertices;

	unsigned int indexCount;
	unsigned int* indices;

	unsigned long long userData;
} EgJoltMesh;

typedef struct {
	unsigned int meshCount;
	EgJoltMesh* meshes;
} EgJoltCompoundMesh;

typedef struct {
	EgJoltVector3 position;
	EgJoltQuaternion rotation;
	EgJoltVector3 linearVelocity;
	EgJoltVector3 angularVelocity;
	float gravityFactor;
	EgJolt_BodyFlags flags;
	unsigned char layer;
} EgJoltBodyState;

typedef struct
{
	EgJoltVector3			stickToFloorStepDown;
	EgJoltVector3			walkStairsStepUp;
	float					walkStairsMinStepForward;
	float					walkStairsStepForwardTest;
	float					walkStairsCosAngleForwardContact;
	EgJoltVector3			walkStairsStepDownExtra;
	unsigned char           layer;

} EgJoltCharacterVirtualUpdateSettings;

enum class EgJolt_GroundState
{
	OnGround,						///< Character is on the ground and can move freely.
	OnSteepGround,					///< Character is on a slope that is too steep and can't climb up any further. The caller should start applying downward velocity if sliding from the slope is desired.
	NotSupported,					///< Character is touching an object, but is not supported by it and should fall. The GetGroundXXX functions will return information about the touched object.
	InAir							///< Character is in the air and is not touching anything.
};

extern "C" {

	EG_EXPORT void egJoltSharedInit();
	EG_EXPORT void egJoltSharedDestroy();

	EG_EXPORT unsigned int egJoltGetMaxBodies();
	EG_EXPORT unsigned int egJoltGetMaxBodyPairs();
	EG_EXPORT unsigned int egJoltGetMaxContactConstraints();

	EG_EXPORT EgJoltInstance egJoltCreateInstance(
		unsigned char maxNumberOfLayers,
		void(*callbackContactAdded)(EgJoltContactArgs),
		void(*callbackContactPersisted)(EgJoltContactArgs),
		bool(*callbackShouldCollide)(unsigned char layer1, unsigned char layer2)
	);
	EG_EXPORT void egJoltDestroyInstance(EgJoltInstance instance);
	EG_EXPORT void egJoltUpdate(EgJoltInstance instance, float deltaTime, int collisionSteps);
	EG_EXPORT void egJoltSetGravity(EgJoltInstance instance, EgJoltVector3 gravity);
	EG_EXPORT void egJoltOptimizeBroadPhase(EgJoltInstance instance);

	EG_EXPORT unsigned int egJoltGetCharacterBodyId(EgJoltInstance instance, EgJoltCharacter character);
	EG_EXPORT bool egJoltAreBodiesColliding(EgJoltInstance instance, unsigned int bodyId1, unsigned int bodyId2);
	EG_EXPORT void egJolt_Body_InvalidateContactCache(EgJoltInstance instance, unsigned int bodyId);
	EG_EXPORT void egJoltBodySetGravityFactor(EgJoltInstance instance, unsigned int bodyId, float gravityFactor);
	EG_EXPORT unsigned int egJoltAddBodyDynamicBox(EgJoltInstance instance, EgJoltVector3 scale, float density, float mass, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state);
	EG_EXPORT unsigned int egJoltAddBodyDynamicSphere(EgJoltInstance instance, float radius, float density, float mass, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state);
	EG_EXPORT unsigned int egJoltAddBodyStaticBox(EgJoltInstance instance, EgJoltVector3 scale, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state);
	EG_EXPORT unsigned int egJoltAddBodyStaticMesh(EgJoltInstance instance, EgJoltVector3* vertices, int vertexCount, unsigned int* indices, int indexCount, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state);
	EG_EXPORT unsigned int egJoltAddBodyStaticCompoundMesh(EgJoltInstance instance, EgJoltCompoundMesh compoundMesh, unsigned long long userData, unsigned int* bodyId, EgJoltBodyState* state);
	EG_EXPORT void egJoltActivateBody(EgJoltInstance instance, unsigned int bodyId);
	EG_EXPORT void egJoltDeactivateBody(EgJoltInstance instance, unsigned int bodyId);
	EG_EXPORT void egJoltRemoveBody(EgJoltInstance instance, unsigned int bodyId);
	EG_EXPORT bool egJoltIsBodyActive(EgJoltInstance instance, unsigned int bodyId);
	EG_EXPORT void egJoltAddBodyImpulse(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 impulse);
	EG_EXPORT void egJoltAddBodyAngularImpulse(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 angularImpulse);
	EG_EXPORT unsigned long long egJoltGetBodyUserData(EgJoltInstance instance, unsigned int bodyId);
	EG_EXPORT void egJoltSetBodyUserData(EgJoltInstance instance, unsigned int bodyId, unsigned long long userData);
	EG_EXPORT void egJoltSetBodyPosition(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position);
	EG_EXPORT void egJoltSetBodyPositionAndRotationAndVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position, EgJoltQuaternion rotation, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity);
	EG_EXPORT void egJoltSetBodyPositionAndVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity);
	EG_EXPORT void egJoltSetBodyVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity);
	EG_EXPORT void egJoltSetBodyVelocityAndActivate(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 linearVelocity, EgJoltVector3 angularVelocity);
	EG_EXPORT EgJoltVector3 egJoltGetBodyPosition(EgJoltInstance instance, unsigned int bodyId);
	EG_EXPORT void egJoltSetBodyPositionAndRotation(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3 position, EgJoltQuaternion rotation);
	EG_EXPORT void egJoltGetBodyPositionAndRotation(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& position, EgJoltQuaternion& rotation);
	EG_EXPORT void egJoltGetBodyCenterOfMassPositionAndRotation(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& position, EgJoltQuaternion& rotation);
	EG_EXPORT void egJoltGetBodyVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& linearVelocity, EgJoltVector3& angularVelocity);
	EG_EXPORT void egJoltGetBodyCenterOfMassPositionAndRotationAndVelocity(EgJoltInstance instance, unsigned int bodyId, EgJoltVector3& position, EgJoltQuaternion& rotation, EgJoltVector3& linearVelocity, EgJoltVector3& angularVelocity);

	EG_EXPORT EgJoltCharacterVirtual egJoltCreateCharacterVirtual(EgJoltInstance instance, EgJoltCharacterSettings& settings, EgJoltVector3 position);
	EG_EXPORT void egJoltDestroyCharacterVirtual(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT void egJoltGetCharacterVirtualWorldTransform(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltMatrix4x4& transform);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualCenterOfMassPosition(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualPosition(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT void egJolt_CharacterVirtual_SetPosition(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltVector3 position);
	EG_EXPORT void egJolt_CharacterVirtual_RefreshContacts(EgJoltInstance instance, EgJoltCharacterVirtual character, unsigned char layer);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualLinearVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT void egJoltSetCharacterVirtualLinearVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltVector3 linearVelocity);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterVirtualGroundVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT EgJolt_GroundState egJolt_CharacterVirtual_GetGroundState(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT bool egJoltIsCharacterVirtualOnSlopeTooSteep(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT void egJolt_CharacterVirtual_SetRotation(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltQuaternion rotation);
	EG_EXPORT void egJolt_CharacterVirtual_SetUp(EgJoltInstance instance, EgJoltCharacterVirtual character, EgJoltVector3 up);
	EG_EXPORT void egJoltUpdateCharacterVirtualGroundVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character);
	EG_EXPORT void egJoltUpdateCharacterVirtual(EgJoltInstance instance, EgJoltCharacterVirtual character, float deltaTime, EgJoltCharacterVirtualUpdateSettings& updateSettings);
	EG_EXPORT void egJoltGetCharacterVirtualActiveDynamicContacts(EgJoltInstance instance, EgJoltCharacterVirtual character, void(*callbackContact)(unsigned int));

	EG_EXPORT EgJoltCharacter egJoltCreateCharacter(EgJoltInstance instance, EgJoltCharacterSettings& settings, EgJoltVector3 position, unsigned long long userData);
	EG_EXPORT void egJoltDestroyCharacter(EgJoltInstance instance, EgJoltCharacter character);
	EG_EXPORT void egJoltGetCharacterWorldTransform(EgJoltInstance instance, EgJoltCharacter character, EgJoltMatrix4x4& transform);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterCenterOfMassPosition(EgJoltInstance instance, EgJoltCharacter character);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterPosition(EgJoltInstance instance, EgJoltCharacter character);
	EG_EXPORT void egJoltSetCharacterPosition(EgJoltInstance instance, EgJoltCharacter character, EgJoltVector3 position);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterLinearVelocity(EgJoltInstance instance, EgJoltCharacter character);
	EG_EXPORT void egJoltSetCharacterLinearVelocity(EgJoltInstance instance, EgJoltCharacter character, EgJoltVector3 linearVelocity);
	EG_EXPORT EgJoltVector3 egJoltGetCharacterGroundVelocity(EgJoltInstance instance, EgJoltCharacter character);
	EG_EXPORT bool egJoltIsCharacterOnGround(EgJoltInstance instance, EgJoltCharacter character);
	EG_EXPORT void egJoltPostUpdateCharacter(EgJoltInstance instance, EgJoltCharacter character, float maxSeparationDistance);

	EG_EXPORT void egJolt_Body_GetState(const EgJoltInstance instance, const unsigned int bodyId, EgJoltBodyState* state);
	EG_EXPORT void egJolt_Body_SetState(const EgJoltInstance instance, unsigned int bodyId, const EgJoltBodyState* state);

	EG_EXPORT int egJolt_Vector3_IsNearZero(EgJoltVector3 v);
	EG_EXPORT EgJoltQuaternion egJolt_Quaternion_Normalize(EgJoltQuaternion q);
	EG_EXPORT int egJolt_Quaternion_IsNormalized(EgJoltQuaternion q);
}

