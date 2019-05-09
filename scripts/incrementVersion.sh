#!/bin/bash

#Variables
VERSION=$(<version)
MAJOR="$(cut -d'.' -f1 <<<"$VERSION")"
MINOR="$(cut -d'.' -f2 <<<"$VERSION")"
BUG="$(cut -d'.' -f3 <<<"$VERSION")"
TWEAK="$(cut -d'.' -f4 <<<"$VERSION")"

#Code
case $1 in
  major) echo $MAJOR
  MAJOR="$(($MAJOR + 1))"
  MINOR=0
  BUG=0
  TWEAK=0;
  ;;
  minor) echo $MINOR
  MINOR="$(($MINOR + 1))"
  BUG=0
  TWEAK=0;
  ;;
  bug) echo $BUG
  BUG="$(($BUG + 1))"
  TWEAK=0;
  ;;
  tweak) echo $TWEAK
  TWEAK="$(($TWEAK + 1))"
  ;;
  *) echo "Error"
  ;;
esac

NEWVERS="$MAJOR.$MINOR.$BUG.$TWEAK"

echo "Current Version: $VERSION"
echo "New Version: $NEWVERS"

echo $NEWVERS > version
