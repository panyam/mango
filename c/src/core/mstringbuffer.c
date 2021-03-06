
#include "mangopub.h"

/**
 * Create a new string with a given capacity.
 *
 * \param   capacity    Capacity of the string.
 *
 * @test(TestStringBufferCreateWithCapacity)
 * MangoStringBuffer *mstr = mango_stringbuffer_with_capacity(32);
 * CHECK(32 == mstr->capacity);
 * CHECK(0 == mstr->length);
 * mango_stringbuffer_free(mstr);
 * @endtest
 */
MangoStringBuffer *mango_stringbuffer_with_capacity(unsigned capacity)
{
    MangoStringBuffer *mstr   = ZNEW(MangoStringBuffer);
    mstr->buffer        = NEW_ARRAY(char, capacity);
    mstr->capacity      = capacity;
    mstr->length        = 0;
    return mstr;
}

/**
 * Create a new string from a buffer.
 *
 * \param   buffer  Buffer of the values to copy.
 * \param   length  Length of the buffer.  If length < 0, then buffer is
 *                  null terminated.
 * \return A new string instance.
 *
 * @test(TestStringBufferCreateFromBuffer)
 * MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
 * CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
 * CHECK_EQUAL(strlen("Hello World"), mstr->length);
 * CHECK(strcmp(mstr->buffer, "Hello World") == 0);
 * mango_stringbuffer_free(mstr);
 * @endtest
 */
MangoStringBuffer *mango_stringbuffer_from_buffer(const char *buffer, int length)
{
    if (length < 0)
        length = strlen(buffer);
    MangoStringBuffer *mstr = mango_stringbuffer_with_capacity(length + 1);
    memcpy(mstr->buffer, buffer, length);
    mstr->length = length;
    mstr->buffer[mstr->length] = 0;
    return mstr;
}

/**
 * Makes a copy of another string.
 *
 * \param   buffer  Buffer of the values to copy.
 * \param   length  Length of the buffer.  If length < 0, then buffer is
 *                  null terminated.
 * \return A new string instance.
 */
MangoStringBuffer *mango_stringbuffer_copy(const MangoStringBuffer *another)
{
    return mango_stringbuffer_from_buffer(another->buffer, another->length);
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_stringbuffer_free(MangoStringBuffer *mstr)
{
    if (mstr->buffer != NULL)
        free(mstr->buffer);
    free(mstr);
}

/**
 * Clears the buffer.
 *
 * \param   mstr    String to be updated.
 *
 * @test(TestStringBufferClear)
 * MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
 * CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
 * CHECK_EQUAL(strlen("Hello World"), mstr->length);
 * CHECK(strcmp(mstr->buffer, "Hello World") == 0);
 * mango_stringbuffer_clear(mstr);
 * CHECK_EQUAL(unsigned(0), mstr->length);
 * mango_stringbuffer_free(mstr);
 * @endtest
 */
void mango_stringbuffer_clear(MangoStringBuffer *mstr)
{
    mstr->length = 0;
}

/**
 * Sets the buffer value.
 *
 * \param   mstr    String to be updated.
 * \param   value   Value to be set to (not necessarily null terminated).
 * \param   length  Length of the input string.
 *
 * @test(TestStringBufferSet)
 * MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
 * CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
 * CHECK_EQUAL(strlen("Hello World"), mstr->length);
 * CHECK(strcmp(mstr->buffer, "Hello World") == 0);
 * mango_stringbuffer_set(mstr, "Hello Magnificient World", -1);
 * CHECK_EQUAL(strlen("Hello Magnificient World"), mstr->length);
 * CHECK(strcmp("Hello Magnificient World", mstr->buffer) == 0);
 * mango_stringbuffer_free(mstr);
 * @endtest
 */
void mango_stringbuffer_set(MangoStringBuffer *mstr, const char *value, int length)
{
    if (length < 0) length = strlen(value);
    mstr->length = 0;
    mango_stringbuffer_append(mstr, value, length);
}

/**
 * Appends a value to the string buffer.
 *
 * \param   mstr    String to be updated.
 * \param   value   Value to be set to (not necessarily null terminated).
 * \param   length  Length of the input string (if < 0, value is null terminated).
 *
 * @test(TestStringBufferAppend)
 * MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
 * CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
 * CHECK_EQUAL(strlen("Hello World"), mstr->length);
 * CHECK(strcmp(mstr->buffer, "Hello World") == 0);
 * mango_stringbuffer_append(mstr, ", I Love You", -1);
 * CHECK_EQUAL(strlen("Hello World, I Love You"), mstr->length);
 * CHECK(strcmp("Hello World, I Love You", mstr->buffer) == 0);
 * mango_stringbuffer_free(mstr);
 * @endtest
 */
void mango_stringbuffer_append(MangoStringBuffer *mstr, const char *value, int length)
{
    if (length < 0) length = strlen(value);
    mango_stringbuffer_ensure_capacity(mstr, length + mstr->length + 1);
    memcpy(mstr->buffer + mstr->length, value, length);
    mstr->length += length;
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends a character.
 *
 * \param   mstr    String to be updated.
 * \param   chr     Character to be appended.
 */
void mango_stringbuffer_append_char(MangoStringBuffer *mstr, char ch)
{
    mango_stringbuffer_ensure_capacity(mstr, mstr->length + 2);
    mstr->buffer[mstr->length++] = ch;
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends a short value.
 *
 * \param   mstr    String to be updated.
 * \param   value   Character to be appended.
 */
void mango_stringbuffer_append_short(MangoStringBuffer *mstr, short value)
{
    int nbytes = sizeof(value);
    mango_stringbuffer_ensure_capacity(mstr, mstr->length + nbytes + 1);
    for (int i = 0;i < nbytes;i++)
    {
        mstr->buffer[mstr->length++] = ((char *)&value)[i];
    }
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends an int value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Short value to be appended.
 */
void mango_stringbuffer_append_int(MangoStringBuffer *mstr, int value)
{
    int nbytes = sizeof(value);
    mango_stringbuffer_ensure_capacity(mstr, mstr->length + nbytes + 1);
    for (int i = 0;i < nbytes;i++)
    {
        mstr->buffer[mstr->length++] = ((char *)&value)[i];
    }
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends long value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Long value to be appended.
 */
void mango_stringbuffer_append_long(MangoStringBuffer *mstr, long value)
{
    int nbytes = sizeof(value);
    mango_stringbuffer_ensure_capacity(mstr, mstr->length + nbytes + 1);
    for (int i = 0;i < nbytes;i++)
    {
        mstr->buffer[mstr->length++] = ((char *)&value)[i];
    }
    mstr->buffer[mstr->length] = 0;
}

/**
 * Formatted appending of contents to the end of the string.
 * Cannot append more than a total of 1024 characters at a time.
 *
 * \param   mstr    String to be appended.
 * \param   fmt     Format of the input.
 * \param   ...     Parameters to be appended.
 *
 * \returns Number of characters added.
 */
int mango_stringbuffer_append_format(MangoStringBuffer *mstr, const char *fmt, ...)
{
    char buff[1024];
    int len;
    va_list(ap);
    va_start(ap, fmt);
    len = vsnprintf(buff, 2047, fmt, ap);
    va_end(ap);
    mango_stringbuffer_append(mstr, buff, len);
    return len;
}

/**
 * Ensures that the string has certain capacity.
 *
 * \param   mstr    String to be updated.
 * \param   newcap  New capacity to be made available in the string.
 *
 * @test(TestStringEnsureCapacity)
 * MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
 * CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
 * CHECK_EQUAL(strlen("Hello World"), mstr->length);
 * CHECK(strcmp(mstr->buffer, "Hello World") == 0);
 * mango_stringbuffer_ensure_capacity(mstr, 128);
 * CHECK_EQUAL(unsigned((128 * 3) / 2), mstr->capacity);
 * mango_stringbuffer_free(mstr);
 * @endtest
 */
void mango_stringbuffer_ensure_capacity(MangoStringBuffer *mstr, size_t newcap)
{
    if (mstr->capacity < newcap)
    {
        newcap          = (newcap * 3) / 2;
        mstr->buffer    = realloc(mstr->buffer, newcap);
        mstr->capacity  = newcap;
    }
}

/**
 * Compares the string contents with another buffer.
 *
 * \param   mstr    String being compared.
 * \param   value   String being compared to.
 * \param   length  Length of the string being compared to.
 *
 * \return -1 if mstr < value, 0 if equal else +1
 */
int mango_stringbuffer_compare(const MangoStringBuffer *mstr, const char *value, int length)
{
    if (mstr == NULL)
        return -1;
    if (length < 0) length = strlen(value);
    int minlen = mstr->length < length ? mstr->length : length;
    for (int i = 0;i < minlen;i++)
    {
        if (mstr->buffer[i] != value[i])
            return mstr->buffer[i] - value[i];
    }
    return mstr->length - length;
}

/**
 * Tells if two strings are equal.
 */
BOOL mango_stringbuffers_are_equal(const MangoStringBuffer *mstr1, const MangoStringBuffer *mstr2)
{
    return mango_stringbuffer_compare(mstr1, mstr2->buffer, mstr2->length) == 0;
}

