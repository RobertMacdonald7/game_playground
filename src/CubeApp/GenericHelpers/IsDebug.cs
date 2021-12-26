namespace CubeApp.GenericHelpers
{
	internal static class IsDebugHelper
	{
		public static bool IsDebug
		{
#if DEBUG
			get { return true; }
#else
			get { return false; }
#endif
		}
	}
}
