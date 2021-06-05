using System;
using System.Runtime.InteropServices;

namespace Consumerv2
{
    class Program
    {

        public const string DllPath = "e:\\projects\\fixed\\linux-windows-csharp\\Hello\\Debug\\Hello.dll";

        //[DllImport(DllPath, CallingConvention = CallingConvention.Cdecl)]
        //public static extern int DisplayHelloFromDLL(int a,int b);

        [DllImport(DllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CryptData([MarshalAs(UnmanagedType.LPStr)] string data);

        [DllImport(DllPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr DecryptData([MarshalAs(UnmanagedType.LPStr)] string encoded_data, int data_size);


        public static string _CryptData(string data)
        {
            IntPtr ptr = CryptData(data);
            // assume returned string is utf-8 encoded
            return PtrToStringUtf8(ptr);
        }
        public static string _DecryptData(string encoded_data, int data_size)
        {
            IntPtr ptr = DecryptData(encoded_data, data_size);
            // assume returned string is utf-8 encoded
            return PtrToStringUtf8(ptr);
        }
        private static string PtrToStringUtf8(IntPtr ptr) // aPtr is nul-terminated
        {
            if (ptr == IntPtr.Zero)
                return "";
            int len = 0;
            while (System.Runtime.InteropServices.Marshal.ReadByte(ptr, len) != 0)
                len++;
            if (len == 0)
                return "";
            byte[] array = new byte[len];
            System.Runtime.InteropServices.Marshal.Copy(ptr, array, 0, len);
            return System.Text.Encoding.UTF8.GetString(array);
        }

        static void Main(string[] args)
        {
            string dataToEncrypt = "Data inicial a encriptar";

            int data_size = dataToEncrypt.Length;
            string resultCrypt = _CryptData(dataToEncrypt);

            Console.WriteLine(resultCrypt);

            string resultDecrypt = _DecryptData(resultCrypt, data_size);

            Console.WriteLine(resultDecrypt);

        }
    }
}
