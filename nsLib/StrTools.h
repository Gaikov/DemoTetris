#ifndef _STR_TOOLS_H_
#define _STR_TOOLS_H_

#include "comm_types.h"
#include "headers.h"

//---------------------------------------------------------
// str
//---------------------------------------------------------
const char*	StrPrintf( const char* fmt, ... );
bool		StrEqual( const char* s1, const char *s2 );
byte		StrHash( const char* str );
const char*	StrTabs( int tabCount );
void		StrReplace( char *str, char chFind, char chReplace );
void		StrCopy( char *str, const char *from, int maxSize = 0 );
int			StrLineCount( const char* str, int len );
const char* StrSkipChars( const char* str, const char* charSet );	//находит первое вхождение символа которого нет в списке charSet
bool		StrCheck( const char* str );
void		StrCharReplace( char *str, char oldCh, char newCh );

//digitCount - число чифр (дозаполняет нулями), 89 -> (0089), если параметр 4
const char*	StrNumber( int num, int digitCount );

/* врзвращает указатель на 
*/
char*		StrToken( const char *strToken, const char *strDelimit, int &resLength );

//---------------------------------------------------------
// nsString:
//---------------------------------------------------------
class nsString
{
public:
	enum { MAX_SIZE = 256 };

public:
	inline nsString();
	inline nsString( const char *str );

	inline operator const char* () const;
	inline nsString& operator = ( const char* str );
	inline bool operator == ( const char* str );
	inline bool operator != ( const char* str );
	inline char& operator [] ( const idx );
	
	void				operator += ( const char* str );
	
	void __cdecl		Format( const char *fmt, ... );
	inline char*		AsChar() { return m_str; }
	void				CopyFrom( const char* str, int length );	//безопасное копирование
	void				Append( char ch );
	int					Length();
	void				ToLower();
	void				ConvFileName();

	friend nsString operator + ( const nsString &s1, const char *s2 );

protected:
	char	m_str[MAX_SIZE];
};

//---------------------------------------------------------
// nsString::nsString:
//---------------------------------------------------------
nsString::nsString()
{
	m_str[0] = 0;
}

//---------------------------------------------------------
// nsString::nsString:
//---------------------------------------------------------
nsString::nsString( const char *str )
{
	*this = str;
}

//---------------------------------------------------------
// nsString::operator const char*:
//---------------------------------------------------------
nsString::operator const char* () const
{
	return m_str;
}

//---------------------------------------------------------
// nsString::operator = :
//---------------------------------------------------------
nsString& nsString::operator = ( const char* str )
{
	if ( str )
	{
		strncpy( m_str, str, MAX_SIZE - 1 );
		m_str[MAX_SIZE - 1] = 0;
	}
	else
		memset( m_str, 0, MAX_SIZE );

	return *this;
}

//---------------------------------------------------------
// nsString::operator ==:
//---------------------------------------------------------
bool nsString::operator == ( const char* str )
{
	if ( !str ) return false;

	const char*	s1 = m_str;
	const char*	s2 = str;
	while ( *s1 && *s2 )
	{
		if ( *s1 != *s2 ) return false;
		s1++;
		s2++;
	}
	
	return *s1 == *s2;
}

//---------------------------------------------------------
// nsString::operator != : 
//---------------------------------------------------------
bool nsString::operator != ( const char* str )
{
	return !(*this == str);
}

//---------------------------------------------------------
// nsString::operator []: 
//---------------------------------------------------------
char& nsString::operator [] ( const idx )
{
	return m_str[idx];
}


#endif
 