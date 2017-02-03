#pragma once

namespace aeEngineSDK
{
	template <typename T>
	using BasicString = std::basic_string<T, std::char_traits<T>, StdAlloc<T>>;

	template <typename T>
	using BasicStringStream = std::basic_stringstream<T, std::char_traits<T>, StdAlloc<T>>;
	
	typedef BasicString<UNICHAR> wString;
	typedef BasicString<ANSICHAR> String;

	typedef BasicStringStream<UNICHAR> wStringStream;
	typedef BasicStringStream<ANSICHAR> StringStream;
	
	class AE_UTILITY_EXPORT aeStringUtil
	{
	public:
		template<class T>
		static Vector<BasicString<T>> Split(const BasicString<T>& A, const BasicString<T>& B)
		{
			Vector<BasicString<T>> V;
			auto i = 0;
			auto pos = A.find(B);
			while (pos != BasicString<T>::npos)
			{
				V.push_back(A.substr(i, pos - i));
				i = ++pos;
				pos = A.find(B, pos);

				if (pos == BasicString<T>::npos)
					V.push_back(A.substr(i, A.length()));
			}
			return V;
		}

		template<class T>
		static Vector<BasicString<T>> Split(const BasicString<T>& S, const T* psz)
		{
			Vector<BasicString<T>> V;
			auto i = 0;
			auto pos = S.find(psz);
			while (pos != BasicString<T>::npos)
			{
				V.push_back(S.substr(i, pos - i));
				i = ++pos;
				pos = S.find(psz, pos);

				if (pos == BasicString<T>::npos)
					V.push_back(S.substr(i, S.length()));
			}
			return V;
		}

		template<class T>
		static Vector<BasicString<T>> Split(const BasicString<T>& S, const T& C)
		{
			Vector<BasicString<T>> V;
			auto i = 0;
			auto pos = S.find(C);
			while (pos != BasicString<T>::npos)
			{
				V.push_back(S.substr(i, pos - i));
				i = ++pos;
				pos = S.find(C, pos);

				if (pos == BasicString<T>::npos)
					V.push_back(S.substr(i, S.length()));
			}
			return V;
		}

		template<class T>
		static Vector<BasicString<T>> Split(const T* psz, const BasicString<T>& B)
		{
			Vector<BasicString<T>> V;
			BasicString<T> A(psz);
			auto i = 0;
			auto pos = A.find(B);
			while (pos != BasicString<T>::npos)
			{
				V.push_back(A.substr(i, pos - i));
				i = ++pos;
				pos = A.find(B, pos);

				if (pos == BasicString<T>::npos)
					V.push_back(A.substr(i, A.length()));
			}
			return V;
		}

		template<class T>
		static Vector<BasicString<T>> Split(const T* psz1, const T* psz2)
		{
			Vector<BasicString<T>> V;
			BasicString<T> S(psz1);
			auto i = 0;
			auto pos = S.find(psz2);
			while (pos != BasicString<T>::npos)
			{
				V.push_back(S.substr(i, pos - i));
				i = ++pos;
				pos = S.find(psz2, pos);

				if (pos == BasicString<T>::npos)
					V.push_back(S.substr(i, S.length()));
			}
			return V;
		}

		template<class T>
		static Vector<BasicString<T>> Split(const T* psz, const T& C)
		{
			Vector<BasicString<T>> V;
			BasicString<T> S(psz);
			auto i = 0;
			auto pos = S.find(C);
			while (pos != BasicString<T>::npos)
			{
				V.push_back(S.substr(i, pos - i));
				i = ++pos;
				pos = S.find(C, pos);

				if (pos == BasicString<T>::npos)
					V.push_back(S.substr(i, S.length()));
			}
			return V;
		}
		
		// trim from start (in place)
		template<class T>
		static void TrimLeft(BasicString<T>& S, const T& C)
		{
			size_t pos = S.find_first_of(C);
			if (pos != S.npos)
				S = S.substr(pos+1);
			else
				S.clear();
		}

		// trim from end (in place)
		template<class T>
		static void TrimRight(BasicString<T>& S, const T& C)
		{
			size_t pos = S.find_last_of(C);
			if (pos != S.npos)
				S.erase(pos);
			else
				S.clear();
		}

		// trim from both ends (in place)
		template<class T>
		static inline void Trim(BasicString<T>& S, const T& C)
		{
			TrimLeft(S, C);
			TrimRight(S, C);
		}

		// trim from start (copying)
		template<class T>
		static inline BasicString<T> TrimmedLeft(BasicString<T> S, const T& C)
		{
			TrimLeft(S, C);
			return S;
		}

		// trim from end (copying)
		template<class T>
		static inline BasicString<T> TrimmedRight(BasicString<T> S, const T& C)
		{
			TrimRight(S, C);
			return S;
		}

		// trim from both ends (copying)
		template<class T>
		static inline BasicString<T> Trimmed(BasicString<T> S, const T& C)
		{
			TrimLeft(S, C);
			TrimRight(S, C);
			return S;
		}

		static inline void ToUpper(const String& Reference, String& Result)
		{
			Result = Reference;
			transform(Result.begin(), Result.end(), Result.begin(), ::toupper);
		}		
		static inline void ToUpper(const wString& Reference, wString& Result)
		{
			Result = Reference;
			transform(Result.begin(), Result.end(), Result.begin(), ::towupper);
		}
		static inline void ToUpper(String& S)
		{
			transform(S.begin(), S.end(), S.begin(), ::toupper);
		}
		static inline void ToUpper(wString& S)
		{
			transform(S.begin(), S.end(), S.begin(), ::towupper);
		}

		static inline void ToLower(const String& Reference, String& Result)
		{
			Result = Reference;
			transform(Result.begin(), Result.end(), Result.begin(), ::tolower);
		}
		static inline void ToLower(const wString& Reference, wString& Result)
		{
			Result = Reference;
			transform(Result.begin(), Result.end(), Result.begin(), ::towlower);
		}
		static inline void ToLower(String& S)
		{
			transform(S.begin(), S.end(), S.begin(), ::tolower);
		}
		static inline void ToLower(wString& S)
		{
			transform(S.begin(), S.end(), S.begin(), ::towlower);
		}

		static inline uint32 StrLen(const ANSICHAR* psz)
		{
			return (uint32)strlen(psz);
		}
		static inline uint32 StrLen(const UNICHAR* psz)
		{
			return (uint32)wcslen(psz);
		}

		template<class T>
		static uint32 StrPos(const BasicString<T>& A, const BasicString<T>& B)
		{
			uint32 i;
			if ((i = A.find(B)) != BasicString<T>::npos)
				return i;
			return BasicString<T>::npos;
		}

		template<class T>
		static uint32 StrPos(const BasicString<T>& S, const T& C)
		{
			uint32 i;
			if ((i = S.find(C)) != BasicString<T>::npos)
				return i;
			return BasicString<T>::npos;
		}

		template<class T>
		static uint32 StrPos(const BasicString<T>& S, const T* psz)
		{
			uint32 i;
			if ((i = S.find(psz)) != BasicString<T>::npos)
				return i;
			return BasicString<T>::npos;
		}
		
		template<class T>
		static uint32 StrPos(const T* psz, const BasicString<T>& B)
		{
			BasicString<T> A(psz);
			uint32 i;
			if ((i = A.find(B)) != BasicString<T>::npos)
				return i;
			return BasicString<T>::npos;
		}

		template<class T>
		static uint32 StrPos(const T* psz, const T& C)
		{
			BasicString<T> S(psz);
			uint32 i;
			if ((i = S.find(C)) != BasicString<T>::npos)
				return i;
			return BasicString<T>::npos;
		}

		template<class T>
		static uint32 StrPos(const T* psz1, const T* psz2)
		{
			BasicString<T> S(psz1);
			uint32 i;
			if ((i = S.find(psz2)) != BasicString<T>::npos)
				return i;
			return BasicString<T>::npos;
		}

		template<class T>
		static inline T* StrStr(const T* psz, const BasicString<T>& B)
		{
			uint32 i;
			if ((i = StrPos(psz, B)) != BasicString<T>::npos)
				return &psz[i];
			return nullptr;
		}

		template<class T>
		static inline T* StrStr(const T* psz, const T& C)
		{
			uint32 i;
			if ((i = StrPos(psz, C)) != BasicString<T>::npos)
				return &psz[i];
			return nullptr;
		}

		template<class T>
		static inline T* StrStr(const T* psz1, const T* psz2)
		{
			uint32 i;
			if ((i = StrPos(psz1, ps2)) != BasicString<T>::npos)
				return &psz[i];
			return nullptr;
		}

		template<class T>
		static BasicString<T> Substr(const BasicString<T>& S, const SIZE_T& Pos = 0, const SIZE_T& Size = BasicString<T>::npos)
		{
			return S.substr(Pos, Size);
		}

		template<class T>
		static BasicString<T> Substr(const T* psz, const SIZE_T& Pos = 0, const SIZE_T& Size = BasicString<T>::npos)
		{
			BasicString<T> S(psz);
			return S.substr(Pos, Size);
		}

		template<class T>
		static BasicString<T> StrCat(const BasicString<T>& A, const BasicString<T>& B)
		{
			BasicString<T> S(A);
			return S += B;
		}

		template<class T>
		static BasicString<T> StrCat(const BasicString<T>& S, const T* psz)
		{
			BasicString<T> Result(S);
			return S += psz;
		}

		template<class T>
		static BasicString<T> StrCat(const T* psz, const BasicString<T>& S)
		{
			BasicString<T> Result(S);
			return S += psz;
		}

		template<class T>
		static BasicString<T> StrCat(const T* psz1, const T* psz2)
		{
			BasicString<T> Result(psz1);
			return S += psz2;
		}

		template<class T>
		static bool StartsWith(const BasicString<T>& A, const BasicString<T>& B)
		{
			if (A.length() < B.length())
				return false;

			return A.find_first_of(B) == 0;
		}

		template<class T>
		static bool StartsWith(const BasicString<T>& S, const T* psz)
		{
			BasicString<T> B(psz);
			if (S.length() < B.length())
				return false;

			return S.find_first_of(B) == 0;
		}

		template<class T>
		static bool StartsWith(const T* psz1, const T* psz2)
		{
			BasicString<T> A(psz1);
			BasicString<T> B(psz2);
			if (A.length() < B.length())
				return false;

			return A.find_first_of(B) == 0;
		}

		template<class T>
		static bool EndsWith(const BasicString<T>& A, const BasicString<T>& B)
		{
			if (A.length() < B.length())
				return false;

			return A.substr(A.length() - B.length()) == B;
		}

		template<class T>
		static bool EndsWith(const BasicString<T>& S, const T* psz)
		{
			BasicString<T> B(psz);
			if (S.length() < B.length())
				return false;

			return S.substr(S.length() - B.length()) == B;
		}

		template<class T>
		static bool EndsWith(const T* psz1, const T* psz2)
		{
			BasicString<T> A(psz1);
			BasicString<T> B(psz2);
			if (A.length() < B.length())
				return false;

			return A.substr(A.length() - B.length()) == B;
		}
	
		static String Wstr2Str(const wString& S)
		{
			/*size_t sz = S.length();
			const wchar_t* p = S.c_str();
			char* tp = new char[sz];
			size_t w = wcstombs(tp, p, sz);
			if (w != sz) {
				delete[] tp;
			}
			String ret(tp);
			delete[] tp;
			return ret;*/
			size_t outputSize = S.length() + 1; // +1 for null terminator
			Vector<ANSICHAR> outputString(outputSize);
			size_t charsConverted = 0;
			const UNICHAR * inputW = S.c_str();
			wcstombs_s(&charsConverted, &outputString[0], outputSize, inputW, S.length());
			if (charsConverted != outputSize) {
				outputString.clear();
			}
			String ret(&outputString[0]);
			outputString.clear();
			return ret;
		}
		static wString Str2Wstr(const String& S)
		{
			/*const char* p = S.c_str();
			size_t len = S.length();
			size_t sz = len * sizeof(wchar_t);
			wchar_t* tp = new wchar_t[sz];
			size_t w = mbstowcs(tp, p, sz);
			if (w != len) {
				delete[] tp;
			}
			wString ret(tp);
			delete[] tp;
			return ret;*/
			size_t outputSize = S.length() + 1; // +1 for null terminator
			Vector<UNICHAR> outputString(outputSize);
			size_t charsConverted = 0;
			const ANSICHAR * input = S.c_str();
			mbstowcs_s(&charsConverted, &outputString[0], outputSize, input, S.length());
			if (charsConverted != outputSize) {
				outputString.clear();
			}
			wString ret(&outputString[0]);
			outputString.clear();
			return ret;
		}

		static inline String Wstr2Str(const UNICHAR* psz)
		{
			return Wstr2Str(wString(psz));
		}
		static inline wString Str2Wstr(const ANSICHAR* psz)
		{
			return Str2Wstr(String(psz));
		}

		static String ExtractFileName(String Path)
		{
			TrimRight(Path, '.'); 
			auto v = Split(Path, '\\'); 
			return *v.rbegin(); 
		}

		static wString ExtractFileNameW(wString Path)
		{
			TrimRight(Path, L'.');
			auto v = Split(Path, L'\\');
			return *v.rbegin();
		}
	};

	template<class T>
	static uint32 ParseUnsignedInt(const BasicString<T>& val, uint32 defaultValue)
	{
		BasicStringStream<T> str(val);
		int64 ret = defaultValue;
		str >> ret;
		if (ret < 0)
		{
			return 0;
		}
		return (uint32)ret;
	}

	template<class T>
	static int32 ParseInt(const BasicString<T>& val, int32 defaultValue)
	{
		BasicStringStream<T> str(val);
		int32 ret = defaultValue;
		str >> ret;
		return (uint32)ret;
	}

	template<class T>
	static float ParseFloat(const BasicString<T>& val, float defaultValue)
	{
		BasicStringStream<T> str(val);
		float ret = defaultValue;
		str >> ret;
		return ret;
	}

	template<class T>
	static double ParseDouble(const BasicString<T>& val, double defaultValue)
	{
		BasicStringStream<T> str(val);
		double ret = defaultValue;
		str >> ret;
		return ret;
	}

	static bool ParseBool(const wString& val, bool defaultValue)
	{
		if (aeStringUtil::StartsWith(val, L"true"))
			return true;
		else
			return defaultValue;
	}

	static bool ParseBool(const String& val, bool defaultValue)
	{
		if (aeStringUtil::StartsWith(val, "true"))
		{
			return true;
		}
		else
		{
			return defaultValue;
		}
	}

	template<class U>
	static BasicString<ANSICHAR> ToString(U in)
	{
		String out = std::to_string(in).c_str();
		return out;
	}

	static BasicString<ANSICHAR> ToString(bool in)
	{
		if (in)
			return BasicString<ANSICHAR>("True");
		else
			return BasicString<ANSICHAR>("False");
	}

	template<class U>
	static BasicString<UNICHAR> ToWString(U in)
	{
		wString out = std::to_wstring(in).c_str();
		return out;
	}

	static BasicString<UNICHAR> ToWString(bool in)
	{
		if (in)
			return BasicString<UNICHAR>(L"True");
		else
			return BasicString<UNICHAR>(L"False");
	}
		
}


