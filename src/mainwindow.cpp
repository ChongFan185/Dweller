#include "mainwindow.h"
#include "simulatewindow.h"

MainWindow::MainWindow()
{
    canvas = new DwellerCanvas;
    setCentralWidget(canvas);

    createActions();
    createMenuBar();
    createSettingBar();
    createStatusBar();
    createToolBar();

}

void MainWindow::on_actionNewFile(){

}

void MainWindow::on_actionOpenFile(){

}

void MainWindow::on_actionSaveFile(){

}

void MainWindow::on_actionSaveAs(){

}

void MainWindow::on_actionExit(){

}

void MainWindow::on_actionCut(){

}

void MainWindow::on_actionCopy(){

}

void MainWindow::on_actionPaste(){

}

void MainWindow::on_actionDelete(){

}

void MainWindow::on_actionSimulate(){
    //SimulateWindow sw;
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/simulator.qml")));
    QQuickView *view = new QQuickView;
    view->setSource(QUrl("qrc:/simulator.qml"));
    view->show();
}

void MainWindow::on_actionSelect(){

}

void MainWindow::on_actionAbout(){

}

void MainWindow::on_actionDrawWall(){

}

void MainWindow::on_actionDrawWindow(){

}
void MainWindow::on_actionDrawDoor(){

}
void MainWindow::on_actionDrawFloor(){

}
void MainWindow::on_actionDrawDevice(){

}

void MainWindow::on_actionShowSetting(){

}

void MainWindow::initScene(){

}

void MainWindow::createMenuBar(){
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addAction(selectAction);
    editMenu->addSeparator();
    editMenu->addAction(drawWallAction);
    editMenu->addAction(drawDoorAction);
    editMenu->addAction(drawWindowAction);
    editMenu->addAction(drawFloorAction);
    editMenu->addAction(drawDeviceAction);

    windowMenu = menuBar()->addMenu(tr("Window"));
    windowMenu->addAction(simulateAction);
    windowMenu->addAction(showSettingAction);

    aboutMenu = menuBar()->addMenu(tr("About"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createStatusBar(){
    statusBarMessage = new QLabel(tr("OK"));
    statusBar()->addWidget(statusBarMessage);
}

void MainWindow::createSettingBar(){
    settingDock = new QDockWidget("Setting",this);
    settingDock->setAllowedAreas(Qt::RightDockWidgetArea);

    settingList = new QListWidget(settingDock);

    settingDock->setWidget(settingList);
    addDockWidget(Qt::RightDockWidgetArea,settingDock);
}

void MainWindow::createToolBar(){
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newFileAction);
    fileToolBar->addAction(openFileAction);
    fileToolBar->addAction(saveFileAction);
    fileToolBar->addSeparator();
    fileToolBar->addAction(cutAction);
    fileToolBar->addAction(copyAction);
    fileToolBar->addAction(pasteAction);
    fileToolBar->addAction(deleteAction);
    fileToolBar->addSeparator();
    fileToolBar->addAction(simulateAction);

    paintToolBar = new QToolBar(tr("paint"));
    paintToolBar->addAction(selectAction);
    paintToolBar->addAction(drawWallAction);
    paintToolBar->addAction(drawDoorAction);
    paintToolBar->addAction(drawWindowAction);
    paintToolBar->addAction(drawFloorAction);
    paintToolBar->addAction(drawDeviceAction);
    addToolBar(Qt::LeftToolBarArea, paintToolBar);
}

void MainWindow::createActions(){
    //file
    newFileAction = new QAction(tr("&New"), this);
    newFileAction->setIcon(QIcon(":/res/creator_new.png"));
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(on_actionNewFile()));

    openFileAction = new QAction(tr("&Open..."), this);
    openFileAction->setIcon(QIcon(":/res/creator_open.png"));
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open an existing spreadsheet file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(on_actionOpenFile()));

    saveFileAction = new QAction(tr("&Save"), this);
    saveFileAction->setIcon(QIcon(":/res/creator_save.png"));
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save the spreadsheet to disk"));
    connect(saveFileAction, SIGNAL(triggered()), this, SLOT(on_actionSaveFile()));

    saveAsFileAction = new QAction(tr("Save &As..."), this);
    saveAsFileAction->setIcon(QIcon(":/res/creator_saveAs.png"));
    saveAsFileAction->setStatusTip(tr("Save the spreadsheet under a new name"));
    connect(saveAsFileAction, SIGNAL(triggered()), this, SLOT(on_actionSaveAs()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_actionExit()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(on_actionAbout()));

    //edit
    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/res/creator_cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(on_actionCut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/res/creator_copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection's contents "
                                "to the clipboard"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(on_actionCopy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/res/creator_paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(on_actionPaste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/res/creator_delete.png"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete the current selection's contents"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_actionDelete()));

    simulateAction = new QAction(tr("&Simulate"), this);
    simulateAction->setIcon(QIcon(":/res/creator_startSimulator.png"));
    simulateAction->setStatusTip(tr("simulate your scene"));
    connect(simulateAction, SIGNAL(triggered()), this, SLOT(on_actionSimulate()));

    showSettingAction = new QAction(tr("Setting Window"), this);
    showSettingAction->setIcon(QIcon(":/res/creator_setting.png"));
    showSettingAction->setStatusTip(tr("show setting dock window"));
    connect(showSettingAction, SIGNAL(triggered()), this, SLOT(on_actionShowSetting()));

    //tool
    selectAction = new QAction(tr("Select"), this);
    selectAction->setIcon(QIcon(":/res/creator_select.png"));
    selectAction->setShortcut(QKeySequence(tr("s")));
    selectAction->setStatusTip(tr("Select item"));
    connect(selectAction, SIGNAL(triggered()), this, SLOT(on_actionSelect()));

    drawWallAction = new QAction(tr("DrawWall"), this);
    drawWallAction->setIcon(QIcon(":/res/creator_wall.png"));
    drawWallAction->setShortcut(QKeySequence(tr("l")));
    drawWallAction->setStatusTip(tr("draw a wall"));
    connect(drawWallAction, SIGNAL(triggered()), this, SLOT(on_actionDrawWall()));

    drawWindowAction = new QAction(tr("DrawWindow"), this);
    drawWindowAction->setIcon(QIcon(":/res/creator_window.png"));
    drawWindowAction->setShortcut(QKeySequence(tr("w")));
    drawWindowAction->setStatusTip(tr("draw a window on a wall"));
    connect(drawWindowAction, SIGNAL(triggered()), this, SLOT(on_actionDrawWindow()));

    drawDoorAction = new QAction(tr("DrawDoor"), this);
    drawDoorAction->setIcon(QIcon(":/res/creator_door.png"));
    drawDoorAction->setShortcut(QKeySequence(tr("d")));
    drawDoorAction->setStatusTip(tr("draw a door on a wall"));
    connect(drawDoorAction, SIGNAL(triggered()), this, SLOT(on_actionDrawDoor()));

    drawFloorAction = new QAction(tr("DrawFloor"), this);
    drawFloorAction->setIcon(QIcon(":/res/creator_floor.png"));
    drawFloorAction->setShortcut(QKeySequence(tr("f")));
    drawFloorAction->setStatusTip(tr("draw a floor"));
    connect(drawFloorAction, SIGNAL(triggered()), this, SLOT(on_actionDrawFloor()));

    drawDeviceAction = new QAction(tr("DrawDevice"), this);
    drawDeviceAction->setIcon(QIcon(":/res/creator_device.png"));
    drawDeviceAction->setShortcut(QKeySequence(tr("v")));
    drawDeviceAction->setStatusTip(tr("set device"));
    connect(drawDeviceAction, SIGNAL(triggered()), this, SLOT(on_actionDrawDevice()));

}