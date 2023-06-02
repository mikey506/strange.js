/*
 * weird.js - Javascript obfuscation compiler
 *
 * Written by Aaron Blakely <aaron@ephasic.org>
 * Copyright (C) 2022 Ephasic Software (https://ephasic.org/wtf.js)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUMS 5

int charCount = 0;
int stringCount = 0;

struct charStruct
{
  char c;
  char *code;
  int size;
} chars[22];

struct stringsStruct
{
  char *str;
  char *code;
  int size;
} strings[4];

typedef struct numberArgs
{
  int len;
  int slen;
  int numbers[MAX_NUMS];
  char *strings[MAX_NUMS];
} numberArgs;

void strlcpy(char *to, const char *from, int len)
{
    memccpy(to, from, '\0', len);
}

int charIndex(char c)
{
  for (int i = 0; i < charCount; i++)
  {
    if (chars[i].c == c)
      return i;
  }

  return 0;
}

int stringIndex(char *str)
{
  for (int i = 0; i < stringCount; i++)
  {
    if (strcmp(str, strings[i].str) == 0)
      return i;
  }

  return -1;
}

int numberStrSize(int n)
{
  if (n > 1)
  {
    return 8 * n - 3;
  }
  else
  {
    return 5 * n;
  }
}

char *number(int n)
{
  char *ret = calloc(n, sizeof(char) * 8);
  char *one = "+!![]";

  for (int i = 0; i < n; i++)
  {
    strcat(ret, one);

    if (i + 1 != n)
    {
      strcat(ret, " + ");
    }
  }

  return ret;
}

void initChar(char c, char *str, numberArgs args)
{
  int codelen = 0, i = 0, j = 0, slen = 0, argcnt = 0, sargcnt = 0, bufsize = 0, stridx = 0;
  char *buf;

  for (i = 0; i < args.len; i++)
  {
    bufsize += numberStrSize(args.numbers[i]) + 1;
  }

  if (args.slen > 0)
  {
    for (i = 0; i < args.slen; i++)
    {
      stridx = stringIndex(args.strings[i]);

      if (strings[stridx].code)
        bufsize += (int)strlen(strings[stridx].code) + 10;

      if (i + 1 != args.slen)
      {
        bufsize += 3;
      }
    }
  }

  codelen = (int)strlen(str);
  chars[charCount].c = c;

  buf = calloc(bufsize + 50, sizeof(char));
  i = 0;

  while (str[i] != '\0')
  {
    if (str[i] == '?')
    {
      sprintf(buf, "%s%s", buf, number(args.numbers[argcnt]));
      j += (int)strlen(number(args.numbers[argcnt]));
      buf[j] = ' ';

      argcnt++;
      i++;
    }
    else if (str[i] == '@')
    {
      stridx = stringIndex(args.strings[sargcnt]);

      if (strings[stridx].code)
      {
        sprintf(buf, "%s%s", buf, strings[stridx].code);
        j += (int)strlen(strings[stridx].code);
      }
      else
      {
        sprintf(buf, "%s'%s'", buf, args.strings[sargcnt]);
        j += (int)strlen(args.strings[sargcnt]) + 2;
      }

      if (sargcnt + 1 != args.slen)
      {
        buf[j] = ' ';
        buf[j + 1] = '+';
        buf[j + 2] = ' ';
        j += 3;
      }

      sargcnt++;
      i++;
    }
    else
    {
      buf[j] = str[i];
      i++;
      j++;
    }
  }

  chars[charCount].code = calloc((int)strlen(buf) + 1, sizeof(char));
  strcpy(chars[charCount].code, buf);
  chars[charCount].size = (int)strlen(buf);
  charCount++;
  free(buf);
}
void initString(char *str)
{
  int codelen = 0;
  char *buf;

  strings[stringCount].str = calloc((int)strlen(str) + 1, sizeof(char));
  strcpy(strings[stringCount].str, str);

  codelen = (int)strlen(str) + 10;
  buf = calloc(codelen, sizeof(char));
  sprintf(buf, "'%s'", str);

  strings[stringCount].code = calloc((int)strlen(buf) + 1, sizeof(char));
  strcpy(strings[stringCount].code, buf);
  strings[stringCount].size = (int)strlen(buf);
  stringCount++;
  free(buf);
}

void initAllChars(numberArgs args)
{
  initChar('a', "aa??", args);
  initChar('b', "aa?aa?", args);
  initChar('c', "aa?@?@?", args);
  initChar('d', "aa?@??", args);
  initChar('e', "a??", args);
  initChar('f', "a?aa?", args);
  initChar('g', "a?@?@?", args);
  initChar('h', "a?@??", args);
  initChar('i', "?@?", args);
  initChar('j', "?@@@", args);
  initChar('k', "?@@?", args);
  initChar('l', "?@??", args);
  initChar('m', "?@?@@", args);
  initChar('n', "?@?@?", args);
  initChar('o', "?@?@?@", args);
  initChar('p', "?@?@?@?", args);
  initChar('q', "?@?@?@?@", args);
  initChar('r', "?@?@?@?@?", args);
  initChar('s', "?@?@?@?@?@", args);
  initChar('t', "?@?@?@?@?@?", args);
  initChar('u', "?@?@?@?@?@?@", args);
}

void initAllStrings()
{
  initString("constructor");
  initString("prototype");
  initString("toString");
  initString("call");
}

int main()
{
  numberArgs args;
  args.len = 3;
  args.slen = 0;
  args.numbers[0] = 1;
  args.numbers[1] = 2;
  args.numbers[2] = 3;

  initAllStrings();
  initAllChars(args);

  printf("Compilation completed successfully.\n");

  return 0;
}
