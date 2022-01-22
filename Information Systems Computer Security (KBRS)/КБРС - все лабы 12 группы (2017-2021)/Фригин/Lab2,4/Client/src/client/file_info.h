#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <QObject>

/**
 * @brief The FileInfo class
 * Used to send file name and contents to model.
 */
class FileInfo : public QObject {
    Q_OBJECT

public:
    FileInfo() = default;
    /**
     * @brief FileInfo Loaded file.
     * @param parent
     * @param filename File name.
     * @param text File contents.
     */
    explicit FileInfo(QObject* parent, QString filename, QString text);
    /**
     * @brief FileInfo File not loaded ctor.
     * @param parent
     * @param reason Reason why file was not loaded.
     */
    explicit FileInfo(QObject* parent, QString reason);
    FileInfo& operator=(FileInfo&& other) noexcept;
    Q_INVOKABLE bool isLoaded();
    Q_INVOKABLE QString reason();
    Q_INVOKABLE QString text();
    Q_INVOKABLE QString filename();

private:
    QString _filename;
    QString _text;
    bool _isLoaded;
    QString _notLoadedReason;
};

#endif // FILE_INFO_H
