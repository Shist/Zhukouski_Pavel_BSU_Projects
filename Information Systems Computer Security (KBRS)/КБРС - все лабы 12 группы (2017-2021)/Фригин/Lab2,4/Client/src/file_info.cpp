#include "client/file_info.h"

FileInfo::FileInfo(QObject *parent, QString filename, QString text)
    : QObject(parent), _isLoaded(true), _filename(filename), _text(text)
{}

FileInfo::FileInfo(QObject *parent, QString reason)
    : _isLoaded(false), _notLoadedReason(reason)
{}

FileInfo &FileInfo::operator=(FileInfo &&other) noexcept
{
    _filename = other._filename;
    _text = other._text;
}

bool FileInfo::isLoaded()
{
    return _isLoaded;
}

QString FileInfo::reason()
{
    return _notLoadedReason;
}

QString FileInfo::text()
{
    return _text;
}

QString FileInfo::filename()
{
    return _filename;
}
