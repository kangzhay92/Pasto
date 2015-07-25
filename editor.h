#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class LineNumber;

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget* parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);

private:
    QWidget* lineNumberArea;
};

class LineNumber : public QWidget
{
public:
    LineNumber(Editor* editor) : QWidget(editor)
    {
        this->editor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE
    {
        return QSize(editor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE
    {
        editor->lineNumberAreaPaintEvent(event);
    }

private:
    Editor* editor;
};

#endif // EDITOR_H
