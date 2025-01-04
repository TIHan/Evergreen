using System.Runtime.InteropServices;

namespace Evergreen.Physics.Backend.Jolt.Interop;

public static unsafe partial class Methods
{
    public static EgJolt_BodyFlags Or(EgJolt_BodyFlags a, EgJolt_BodyFlags b)
    {
        return (EgJolt_BodyFlags)(unchecked((byte)(a) | (byte)(b)));
    }

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSharedInit();

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSharedDestroy();

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltGetMaxBodies();

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltGetMaxBodyPairs();

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltGetMaxContactConstraints();

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgJoltInstance egJoltCreateInstance([NativeTypeName("void (*)(EgJoltContactArgs)")] delegate* unmanaged[Cdecl]<EgJoltContactArgs, void> callbackContactAdded, [NativeTypeName("void (*)(EgJoltContactArgs)")] delegate* unmanaged[Cdecl]<EgJoltContactArgs, void> callbackContactPersisted);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltDestroyInstance(EgJoltInstance instance);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltUpdate(EgJoltInstance instance, float deltaTime, int collisionSteps);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetGravity(EgJoltInstance instance, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 gravity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltOptimizeBroadPhase(EgJoltInstance instance);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltGetCharacterBodyId(EgJoltInstance instance, EgJoltCharacter character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egJoltAreBodiesColliding(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId1, [NativeTypeName("unsigned int")] uint bodyId2);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJolt_Body_InvalidateContactCache(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltBodySetGravityFactor(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, float gravityFactor);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltAddBodyDynamicBox(EgJoltInstance instance, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 scale, float density, float mass, [NativeTypeName("unsigned long long")] ulong userData, [NativeTypeName("unsigned int *")] uint* bodyId, EgJoltBodyState* state);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltAddBodyDynamicSphere(EgJoltInstance instance, float radius, float density, float mass, [NativeTypeName("unsigned long long")] ulong userData, [NativeTypeName("unsigned int *")] uint* bodyId, EgJoltBodyState* state);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltAddBodyStaticBox(EgJoltInstance instance, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 scale, [NativeTypeName("unsigned long long")] ulong userData, [NativeTypeName("unsigned int *")] uint* bodyId, EgJoltBodyState* state);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltAddBodyStaticMesh(EgJoltInstance instance, [NativeTypeName("EgJoltVector3 *")] System.Numerics.Vector3* vertices, int vertexCount, [NativeTypeName("unsigned int *")] uint* indices, int indexCount, [NativeTypeName("unsigned long long")] ulong userData, [NativeTypeName("unsigned int *")] uint* bodyId, EgJoltBodyState* state);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned int")]
    public static extern uint egJoltAddBodyStaticCompoundMesh(EgJoltInstance instance, EgJoltCompoundMesh compoundMesh, [NativeTypeName("unsigned long long")] ulong userData, [NativeTypeName("unsigned int *")] uint* bodyId, EgJoltBodyState* state);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltActivateBody(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltDeactivateBody(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltRemoveBody(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egJoltIsBodyActive(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltAddBodyImpulse(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 impulse);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltAddBodyAngularImpulse(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 angularImpulse);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("unsigned long long")]
    public static extern ulong egJoltGetBodyUserData(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetBodyUserData(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("unsigned long long")] ulong userData);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetBodyPosition(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetBodyPositionAndRotationAndVelocity(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position, [NativeTypeName("EgJoltQuaternion")] System.Numerics.Quaternion rotation, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 linearVelocity, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 angularVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetBodyPositionAndVelocity(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 linearVelocity, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 angularVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetBodyVelocity(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 linearVelocity, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 angularVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetBodyVelocityAndActivate(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 linearVelocity, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 angularVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetBodyPosition(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetBodyPositionAndRotation(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position, [NativeTypeName("EgJoltQuaternion")] System.Numerics.Quaternion rotation);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltGetBodyPositionAndRotation(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3 &")] System.Numerics.Vector3* position, [NativeTypeName("EgJoltQuaternion &")] System.Numerics.Quaternion* rotation);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltGetBodyCenterOfMassPositionAndRotation(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3 &")] System.Numerics.Vector3* position, [NativeTypeName("EgJoltQuaternion &")] System.Numerics.Quaternion* rotation);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltGetBodyVelocity(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3 &")] System.Numerics.Vector3* linearVelocity, [NativeTypeName("EgJoltVector3 &")] System.Numerics.Vector3* angularVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltGetBodyCenterOfMassPositionAndRotationAndVelocity(EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("EgJoltVector3 &")] System.Numerics.Vector3* position, [NativeTypeName("EgJoltQuaternion &")] System.Numerics.Quaternion* rotation, [NativeTypeName("EgJoltVector3 &")] System.Numerics.Vector3* linearVelocity, [NativeTypeName("EgJoltVector3 &")] System.Numerics.Vector3* angularVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgJoltCharacterVirtual egJoltCreateCharacterVirtual(EgJoltInstance instance, [NativeTypeName("EgJoltCharacterSettings &")] EgJoltCharacterSettings* settings, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltDestroyCharacterVirtual(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltGetCharacterVirtualWorldTransform(EgJoltInstance instance, EgJoltCharacterVirtual character, [NativeTypeName("EgJoltMatrix4x4 &")] System.Numerics.Matrix4x4* transform);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterVirtualCenterOfMassPosition(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterVirtualPosition(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJolt_CharacterVirtual_SetPosition(EgJoltInstance instance, EgJoltCharacterVirtual character, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJolt_CharacterVirtual_RefreshContacts(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterVirtualLinearVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetCharacterVirtualLinearVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 linearVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterVirtualGroundVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgJolt_GroundState egJolt_CharacterVirtual_GetGroundState(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egJoltIsCharacterVirtualOnSlopeTooSteep(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJolt_CharacterVirtual_SetRotation(EgJoltInstance instance, EgJoltCharacterVirtual character, [NativeTypeName("EgJoltQuaternion")] System.Numerics.Quaternion rotation);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJolt_CharacterVirtual_SetUp(EgJoltInstance instance, EgJoltCharacterVirtual character, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 up);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltUpdateCharacterVirtualGroundVelocity(EgJoltInstance instance, EgJoltCharacterVirtual character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltUpdateCharacterVirtual(EgJoltInstance instance, EgJoltCharacterVirtual character, float deltaTime, [NativeTypeName("EgJoltCharacterVirtualUpdateSettings &")] EgJoltCharacterVirtualUpdateSettings* updateSettings);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltGetCharacterVirtualActiveDynamicContacts(EgJoltInstance instance, EgJoltCharacterVirtual character, [NativeTypeName("void (*)(unsigned int)")] delegate* unmanaged[Cdecl]<uint, void> callbackContact);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern EgJoltCharacter egJoltCreateCharacter(EgJoltInstance instance, [NativeTypeName("EgJoltCharacterSettings &")] EgJoltCharacterSettings* settings, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position, [NativeTypeName("unsigned long long")] ulong userData);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltDestroyCharacter(EgJoltInstance instance, EgJoltCharacter character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltGetCharacterWorldTransform(EgJoltInstance instance, EgJoltCharacter character, [NativeTypeName("EgJoltMatrix4x4 &")] System.Numerics.Matrix4x4* transform);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterCenterOfMassPosition(EgJoltInstance instance, EgJoltCharacter character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterPosition(EgJoltInstance instance, EgJoltCharacter character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetCharacterPosition(EgJoltInstance instance, EgJoltCharacter character, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 position);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterLinearVelocity(EgJoltInstance instance, EgJoltCharacter character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltSetCharacterLinearVelocity(EgJoltInstance instance, EgJoltCharacter character, [NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 linearVelocity);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltVector3")]
    public static extern System.Numerics.Vector3 egJoltGetCharacterGroundVelocity(EgJoltInstance instance, EgJoltCharacter character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("bool")]
    public static extern byte egJoltIsCharacterOnGround(EgJoltInstance instance, EgJoltCharacter character);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJoltPostUpdateCharacter(EgJoltInstance instance, EgJoltCharacter character, float maxSeparationDistance);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJolt_Body_GetState([NativeTypeName("const EgJoltInstance")] EgJoltInstance instance, [NativeTypeName("const unsigned int")] uint bodyId, EgJoltBodyState* state);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern void egJolt_Body_SetState([NativeTypeName("const EgJoltInstance")] EgJoltInstance instance, [NativeTypeName("unsigned int")] uint bodyId, [NativeTypeName("const EgJoltBodyState *")] EgJoltBodyState* state);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egJolt_Vector3_IsNearZero([NativeTypeName("EgJoltVector3")] System.Numerics.Vector3 v);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    [return: NativeTypeName("EgJoltQuaternion")]
    public static extern System.Numerics.Quaternion egJolt_Quaternion_Normalize([NativeTypeName("EgJoltQuaternion")] System.Numerics.Quaternion q);

    [DllImport("Evergreen.Physics.Backend.Jolt.Native.dll", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
    public static extern int egJolt_Quaternion_IsNormalized([NativeTypeName("EgJoltQuaternion")] System.Numerics.Quaternion q);
}
