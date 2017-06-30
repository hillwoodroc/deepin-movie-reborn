#ifndef _DMR_MAIN_WINDOW_H
#define _DMR_MAIN_WINDOW_H 

#include <QObject>
#include <DMainWindow>
#include <DTitlebar>
#include <DPlatformWindowHandle>
#include <QtWidgets>
#include "actions.h"

DWIDGET_USE_NAMESPACE

namespace dmr {
class MpvProxy;
class ToolboxProxy;
class EventMonitor;
class PlaylistWidget;

class MainWindow: public QWidget {
    Q_OBJECT
    Q_PROPERTY(QMargins frameMargins READ frameMargins NOTIFY frameMarginsChanged)
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMargins frameMargins() const;
    MpvProxy* proxy() { return _proxy; }
    DTitlebar* titlebar() { return _titlebar; }
    ToolboxProxy* toolbox() { return _toolbox; }
    void requestAction(ActionKind, bool fromUI = false);

signals:
    void frameMarginsChanged();

    
    void windowEntered();
    void windowLeaved();

public slots:
    void play(const QFileInfo& fi);
    void updateProxyGeometry();

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void contextMenuEvent(QContextMenuEvent *cme) override;
    void paintEvent(QPaintEvent*) override;

protected slots:
    void menuItemInvoked(QAction *action);
    void onApplicationStateChanged(Qt::ApplicationState e);
    void onBindingsChanged();
    void updateActionsState();
    void onThemeChanged();
    void updatePlayState();

    void suspendToolsWindow();
    void resumeToolsWindow();

#ifdef USE_DXCB
    void onMonitorButtonPressed(int x, int y);
    void onMonitorMotionNotify(int x, int y);
    void onMonitorButtonReleased(int x, int y);
#endif

private:
    void handleSettings();
    void updateSizeConstraints();
    void reflectActionToUI(ActionKind);

private:
    MpvProxy *_proxy {nullptr};
    DTitlebar *_titlebar {nullptr};
    ToolboxProxy *_toolbox {nullptr};
    PlaylistWidget *_playlist {nullptr};
    QWidget *_center {nullptr};
    QLabel *_playState {nullptr};

    DPlatformWindowHandle *_handle {nullptr};
    QMargins _cachedMargins;
    EventMonitor *_evm {nullptr};

    //toggle-able states
    bool _lightTheme {false};
    bool _windowAbove {false};
};
};

#endif /* ifndef _MAIN_WINDOW_H */


