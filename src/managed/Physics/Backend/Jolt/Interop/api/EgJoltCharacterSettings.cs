namespace Evergreen.Physics.Backend.Jolt.Interop;

public partial struct EgJoltCharacterSettings
{
    public float maxSlopeAngle;

    public float maxStrength;

    public float padding;

    public float penetrationRecoverySpeed;

    public float predictiveContactDistance;

    public float standingHeight;

    public float standingRadius;

    public float crouchingHeight;

    public float crouchingRadius;

    public float mass;

    [NativeTypeName("unsigned char")]
    public byte layer;
}
