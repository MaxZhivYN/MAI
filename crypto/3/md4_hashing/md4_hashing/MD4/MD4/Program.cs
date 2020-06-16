using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;

static class Md4
{
	private static uint A, B, C, D;
	private static uint[] X;

	private static Func<uint, uint, uint, uint> F = (x, y, z) => (x & y) | (~x & z);
	private static Func<uint, uint, uint, uint> G = (x, y, z) => (x & y) | (x & z) | (y & z);
	private static Func<uint, uint, uint, uint> H = (x, y, z) => x ^ y ^ z;

	private static Func<uint, uint, uint> leftRotate = (x, y) => x << (int)y | x >> 32 - (int)y;

	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND10 = (a, b, c, d, x, m) => A = leftRotate((a + F(b, c, d) + x), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND11 = (d, a, b, c, x, m) => D = leftRotate((d + F(a, b, c) + x), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND12 = (c, d, a, b, x, m) => C = leftRotate((c + F(d, a, b) + x), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND13 = (b, c, d, a, x, m) => B = leftRotate((b + F(c, d, a) + x), m);

	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND20 = (a, b, c, d, x, m) => A = leftRotate((a + G(b, c, d) + x + (uint)0x5a827999), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND21 = (d, a, b, c, x, m) => D = leftRotate((d + G(a, b, c) + x + (uint)0x5a827999), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND22 = (c, d, a, b, x, m) => C = leftRotate((c + G(d, a, b) + x + (uint)0x5a827999), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND23 = (b, c, d, a, x, m) => B = leftRotate((b + G(c, d, a) + x + (uint)0x5a827999), m);

	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND30 = (a, b, c, d, x, m) => A = leftRotate((a + H(b, c, d) + x + (uint)0x6ed9eba1), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND31 = (d, a, b, c, x, m) => D = leftRotate((d + H(a, b, c) + x + (uint)0x6ed9eba1), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND32 = (c, d, a, b, x, m) => C = leftRotate((c + H(d, a, b) + x + (uint)0x6ed9eba1), m);
	private static Func<uint, uint, uint, uint, uint, ushort, uint> ROUND33 = (b, c, d, a, x, m) => B = leftRotate((b + H(c, d, a) + x + (uint)0x6ed9eba1), m);

	
	public static string Md4Hash(string input, int roundsCount)
	{
		byte[] bytesRead = Encoding.UTF8.GetBytes(input);

		if (roundsCount < 1 || roundsCount > 3)
			throw new Exception("Rounds error (chose 1, 2 or 3 rounds count)");

		List<byte> bytes = new List<byte>();

		foreach (var by in bytesRead)
		{
			bytes.Add(by);
		}

		uint bitCount = (uint)(bytes.Count) * 8;

		bytes.Add(128);
		while (bytes.Count % 64 != 56)
		{
			bytes.Add(0);
		}

		var uints = new List<uint>();
		for (int i = 0; i + 3 < bytes.Count; i += 4)
		{
			uints.Add(bytes[i] | (uint)bytes[i + 1] << 8 | (uint)bytes[i + 2] << 16 | (uint)bytes[i + 3] << 24);
		}

		uints.Add(bitCount);
		uints.Add(0);

		A = 0x67452301;
		B = 0xefcdab89;
		C = 0x98badcfe;
		D = 0x10325476;


		for (int i = 0; i < uints.Count() / 16; i++)
		{
			X = new uint[16];
			for (int j = 0; j < 16; j++)
			{
				X[j] = uints[i * 16 + j];
			}

			uint AA = A;
			uint BB = B;
			uint CC = C;
			uint DD = D;


			if (roundsCount >= 1)
			{
				ROUND10(A, B, C, D, X[0], 3);
				ROUND11(D, A, B, C, X[1], 7);
				ROUND12(C, D, A, B, X[2], 11);
				ROUND13(B, C, D, A, X[3], 19);
				ROUND10(A, B, C, D, X[4], 3);
				ROUND11(D, A, B, C, X[5], 7);
				ROUND12(C, D, A, B, X[6], 11);
				ROUND13(B, C, D, A, X[7], 19);
				ROUND10(A, B, C, D, X[8], 3);
				ROUND11(D, A, B, C, X[9], 7);
				ROUND12(C, D, A, B, X[10], 11);
				ROUND13(B, C, D, A, X[11], 19);
				ROUND10(A, B, C, D, X[12], 3);
				ROUND11(D, A, B, C, X[13], 7);
				ROUND12(C, D, A, B, X[14], 11);
				ROUND13(B, C, D, A, X[15], 19);
			}

			if (roundsCount >= 2)
			{
				ROUND20(A, B, C, D, X[0], 3);
				ROUND21(D, A, B, C, X[4], 5);
				ROUND22(C, D, A, B, X[8], 9);
				ROUND23(B, C, D, A, X[12], 13);
				ROUND20(A, B, C, D, X[1], 3);
				ROUND21(D, A, B, C, X[5], 5);
				ROUND22(C, D, A, B, X[9], 9);
				ROUND23(B, C, D, A, X[13], 13);
				ROUND20(A, B, C, D, X[2], 3);
				ROUND21(D, A, B, C, X[6], 5);
				ROUND22(C, D, A, B, X[10], 9);
				ROUND23(B, C, D, A, X[14], 13);
				ROUND20(A, B, C, D, X[3], 3);
				ROUND21(D, A, B, C, X[7], 5);
				ROUND22(C, D, A, B, X[11], 9);
				ROUND23(B, C, D, A, X[15], 13);
			}

			if (roundsCount >= 3)
			{
				ROUND30(A, B, C, D, X[0], 3);
				ROUND31(D, A, B, C, X[8], 9);
				ROUND32(C, D, A, B, X[4], 11);
				ROUND33(B, C, D, A, X[12], 15);
				ROUND30(A, B, C, D, X[2], 3);
				ROUND31(D, A, B, C, X[10], 9);
				ROUND32(C, D, A, B, X[6], 11);
				ROUND33(B, C, D, A, X[14], 15);
				ROUND30(A, B, C, D, X[1], 3);
				ROUND31(D, A, B, C, X[9], 9);
				ROUND32(C, D, A, B, X[5], 11);
				ROUND33(B, C, D, A, X[13], 15);
				ROUND30(A, B, C, D, X[3], 3);
				ROUND31(D, A, B, C, X[11], 9);
				ROUND32(C, D, A, B, X[7], 11);
				ROUND33(B, C, D, A, X[15], 15);
			}


			A += AA;
			B += BB;
			C += CC;
			D += DD;
		}

		byte[] exportBytes = new[] { A, B, C, D }.SelectMany(BitConverter.GetBytes).ToArray();
		return BitConverter.ToString(exportBytes).Replace("-", "").ToLower();
	}

	public static string RandomString(int length)
	{
		Random random = new Random();
		const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		
		return new string(Enumerable.Repeat(chars, length)
		  .Select(s => s[random.Next(s.Length)]).ToArray());
	}

	private static readonly string inputFileName = "in";
	private static readonly string outputFileName = "out";


	static void Main()
	{
		int choice;
		do
		{
			Console.WriteLine("1) Make random strings in file.txt");
			Console.WriteLine("2) Make hash from file.txt in this folder");
			Console.WriteLine("3) Differential cryptanalysis of file.txt");
			Console.WriteLine("4) EXIT");
			Console.WriteLine();

			choice = int.Parse(Console.ReadLine());

			switch (choice)
			{
				case 1:
					using (StreamWriter sw = File.CreateText(Path.Combine(Environment.CurrentDirectory, inputFileName + ".txt")))
					{
						Random random = new Random();

						Console.WriteLine("Test count:");
						int testCount = int.Parse(Console.ReadLine());

						sw.WriteLine(testCount);
						for (int i = 0; i < testCount; ++i)
						{
							const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

							sw.WriteLine(new string(Enumerable.Repeat(chars, random.Next(1, 100))
							  .Select(s => s[random.Next(s.Length)]).ToArray()));
						}
					}
					break;

				case 2:
					for (int roundCount = 1; roundCount <= 3; ++roundCount)
					{
						using (var sr = new StreamReader(Path.Combine(Environment.CurrentDirectory, inputFileName + ".txt")))
						{
							using (var sw = File.CreateText(Path.Combine(Environment.CurrentDirectory, outputFileName + roundCount + ".txt")))
							{
								int testCount = int.Parse(sr.ReadLine());
								for (int i = 0; i < testCount; ++i)
								{
									sw.WriteLine(Md4Hash(sr.ReadLine(), roundCount));
								}
							}
						}
					}
					break;

				case 3:
					for (int roundCount = 1; roundCount <= 3; ++roundCount)
					{
						using (var sr = new StreamReader(Path.Combine(Environment.CurrentDirectory, inputFileName + ".txt")))
						{
							int testCount = int.Parse(sr.ReadLine());
							byte deltaX = 1;
							double result = 0;
							for (int t = 0; t < testCount; ++t)
							{
								string str = sr.ReadLine();

								byte[] strBytes = Encoding.UTF8.GetBytes(str);
								strBytes[strBytes.Length - 1] ^= deltaX;
								string x = Encoding.Default.GetString(strBytes);

								string strHash = Md4Hash(str, roundCount);
								string xHash = Md4Hash(x, roundCount);

								byte[] strHashBytes = Encoding.UTF8.GetBytes(strHash);
								byte[] xHashBytes = Encoding.UTF8.GetBytes(xHash);


								for (int i = 0; i < strHashBytes.Length; ++i)
								{
									result += strHashBytes[i] ^ xHashBytes[i];
								}
							}
							result /= testCount;
							Console.WriteLine($"Rounds: {roundCount}	Dif bits: {result}");
						}
					}

					
					break;

				case 4:
					return;

				default:
					Console.WriteLine("Bad index");
					break;
			}
		} while (true);
	}
}