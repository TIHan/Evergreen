namespace Evergreen.Physics.Backend.Jolt.Interop;

public partial struct EgJoltCharacterVirtualUpdateSettings
{
    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 stickToFloorStepDown;

    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 walkStairsStepUp;

    public float walkStairsMinStepForward;

    public float walkStairsStepForwardTest;

    public float walkStairsCosAngleForwardContact;

    [NativeTypeName("EgJoltVector3")]
    public System.Numerics.Vector3 walkStairsStepDownExtra;

    [NativeTypeName("unsigned char")]
    public byte layer;
}
