#include "QBP_Note.h"



CQBPNote::CQBPNote()
{
}

CQBPNote::CQBPNote(const CQBPNote &obj)
{
    tick     =obj.tick;
    duration =obj.duration;
    pitch    =obj.pitch;
    command  =obj.command;
}

CQBPNote & CQBPNote::operator = (const CQBPNote& other)
{
    tick     =other.tick;
    duration =other.duration;
    pitch    =other.pitch;
    command  =other.command;
    return *this;
}

CQBPNote::~CQBPNote()
{
}
