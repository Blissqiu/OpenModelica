/*
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-2014, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL) VERSION 1.2.
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES
 * RECIPIENT'S ACCEPTANCE OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3,
 * ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 */
/*
 *
 * @author Adeel Asghar <adeel.asghar@liu.se>
 *
 * RCS: $Id$
 *
 */

#ifndef OMCPROXY_H
#define OMCPROXY_H

#include "OpenModelicaScriptingAPIQt.h"
#include "MainWindow.h"
#include "Component.h"
#include "StringHandler.h"
#include "Utilities.h"

class MainWindow;
class CustomExpressionBox;
class ComponentInfo;
class StringHandler;
class OMCInterface;

struct cachedOMCCommand
{
  QString mOMCCommand;
  QString mOMCCommandResult;
};

class OMCProxy : public QObject
{
  Q_OBJECT
private:
  bool mHasInitialized;
  QString mResult;
  QWidget *mpOMCLoggerWidget;
  CustomExpressionBox *mpExpressionTextBox;
  QPushButton *mpOMCLoggerSendButton;
  QPlainTextEdit *mpOMCLoggerTextBox;
  Label *mpOMCLoggerEnableHintLabel;
  QString mObjectRefFile;
  QList<QString> mCommandsList;
  int mCurrentCommandIndex;
  QFile mCommunicationLogFile;
  QTextStream mCommunicationLogFileTextStream;
  QFile mCommandsMosFile;
  QTextStream mCommandsLogFileTextStream;
  MainWindow *mpMainWindow;
  int mAnnotationVersion;
  QMap<QString, QList<cachedOMCCommand> > mCachedOMCCommandsMap;
  OMCInterface *mpOMCInterface;
public:
  OMCProxy(MainWindow *pMainWindow);
  ~OMCProxy();
  void enableCustomExpression(bool enable);
  void getPreviousCommand();
  void getNextCommand();
  cachedOMCCommand getcachedOMCCommand(QString className, QString command);
  void cacheOMCCommand(QString className, QString command, QString commandResult);
  void removeCachedOMCCommand(QString className);
  bool initializeOMC();
  void quitOMC();
  void sendCommand(const QString expression, bool cacheCommand = false, QString className = QString(), bool dontUseCachedCommand = false);
  void setResult(QString value);
  QString getResult();
  void exitApplication();
  void removeObjectRefFile();
  QString getErrorString(bool warningsAsErrors = false);
  bool printMessagesStringInternal();
  int getMessagesStringInternal();
  void setCurrentError(int errorIndex);
  QString getErrorFileName();
  bool getErrorReadOnly();
  int getErrorLineStart();
  int getErrorColumnStart();
  int getErrorLineEnd();
  int getErrorColumnEnd();
  QString getErrorMessage();
  QString getErrorKind();
  QString getErrorLevel();
  QString getVersion(QString className = QString("OpenModelica"));
  void loadSystemLibraries(QSplashScreen *pSplashScreen);
  void loadUserLibraries(QSplashScreen *pSplashScreen);
  QStringList getClassNames(QString className = QString("AllLoadedClasses"), bool recursive = false, bool qualified = "false",
                            bool sort = false, bool builtin = false, bool showProtected = "true");
  QStringList searchClassNames(QString searchText, bool findInText = "false");
  OMCInterface::getClassInformation_res getClassInformation(QString className);
  bool isPackage(QString className);
  bool isBuiltinType(QString typeName);
  QString getBuiltinType(QString typeName);
  bool isWhat(StringHandler::ModelicaClasses type, QString className);
  bool isProtectedClass(QString className, QString nestedClassName);
  bool isPartial(QString className);
  StringHandler::ModelicaClasses getClassRestriction(QString className);
  QString getParameterValue(QString className, QString parameter);
  QStringList getComponentModifierNames(QString className, QString name);
  QString getComponentModifierValue(QString className, QString name);
  bool setComponentModifierValue(QString className, QString name, QString modifierValue);
  QStringList getExtendsModifierNames(QString className, QString extendsClassName);
  QString getExtendsModifierValue(QString className, QString extendsClassName, QString modifierName);
  bool setExtendsModifierValue(QString className, QString extendsClassName, QString modifierName, QString modifierValue);
  bool isExtendsModifierFinal(QString className, QString extendsClassName, QString modifierName);
  QString getIconAnnotation(QString className);
  QString getDiagramAnnotation(QString className);
  int getConnectionCount(QString className);
  QString getNthConnection(QString className, int num);
  QString getNthConnectionAnnotation(QString className, int num);
  int getInheritanceCount(QString className);
  QString getNthInheritedClass(QString className, int num);
  QList<ComponentInfo*> getComponents(QString className);
  QStringList getComponentAnnotations(QString className);
  QString getDocumentationAnnotation(QString className);
  QString getClassComment(QString className);
  QString changeDirectory(QString directory = QString(""));
  bool loadModel(QString className, QString priorityVersion = QString("default"), bool notify = false, QString languageStandard = QString(""),
                 bool requireExactVersion = false);
  bool loadFile(QString fileName, QString encoding = Helper::utf8, bool uses = true);
  bool loadString(QString value, QString fileName, QString encoding = Helper::utf8, bool checkError = true);
  QList<QString> parseFile(QString fileName, QString encoding = Helper::utf8);
  QList<QString> parseString(QString value, QString fileName);
  bool createClass(QString type, QString className, QString extendsClass);
  bool createSubClass(QString type, QString className, QString parentClassName, QString extendsClass);
  bool existClass(QString className);
  bool renameClass(QString oldName, QString newName);
  bool deleteClass(QString className);
  QString getSourceFile(QString className);
  bool setSourceFile(QString className, QString path);
  bool save(QString className);
  bool saveModifiedModel(QString modelText);
  bool saveTotalSCode(QString fileName, QString className);
  QString list(QString className);
  QString instantiateModel(QString className);
  bool addClassAnnotation(QString className, QString annotation);
  QString getDefaultComponentName(QString className);
  QString getDefaultComponentPrefixes(QString className);
  bool addComponent(QString name, QString className, QString componentName, QString placementAnnotation);
  bool deleteComponent(QString name, QString componentName);
  bool renameComponent(QString className, QString oldName, QString newName);
  bool updateComponent(QString name, QString className, QString componentName, QString placementAnnotation);
  bool renameComponentInClass(QString className, QString oldName, QString newName);
  bool updateConnection(QString from, QString to, QString className, QString annotation);
  bool setComponentProperties(QString className, QString componentName, QString isFinal, QString isFlow, QString isProtected,
                              QString isReplaceAble, QString variability, QString isInner, QString isOuter, QString causality);
  bool setComponentComment(QString className, QString componentName, QString comment);
  bool setComponentDimensions(QString className, QString componentName, QString dimensions);
  bool addConnection(QString from, QString to, QString className, QString annotation);
  bool deleteConnection(QString from, QString to, QString className);
  bool simulate(QString className, QString simualtionParameters);
  bool buildModel(QString className, QString simualtionParameters);
  bool translateModel(QString className, QString simualtionParameters);
  QStringList readSimulationResultVars(QString fileName);
  bool closeSimulationResultFile();
  QString checkModel(QString className);
  bool ngspicetoModelica(QString fileName);
  QString checkAllModelsRecursive(QString className);
  bool isExperiment(QString className);
  QStringList getSimulationOptions(QString className, double defaultTolerance = 1e-4);
  bool translateModelFMU(QString className, double version, QString fileNamePrefix);
  bool translateModelXML(QString className);
  QString importFMU(QString fmuName, QString outputDirectory, int logLevel, bool debugLogging, bool generateInputConnectors, bool generateOutputConnectors);
  QString getMatchingAlgorithm();
  void getAvailableMatchingAlgorithms(QStringList *choices, QStringList *comments);
  bool setMatchingAlgorithm(QString matchingAlgorithm);
  QString getIndexReductionMethod();
  void getAvailableIndexReductionMethods(QStringList *choices, QStringList *comments);
  bool setIndexReductionMethod(QString method);
  bool setCommandLineOptions(QString options);
  bool clearCommandLineOptions();
  QString makeDocumentationUriToFileName(QString documentation);
  QString uriToFilename(QString uri);
  QString getModelicaPath();
  QStringList getAvailableLibraries();
  QString getDerivedClassModifierValue(QString className, QString modifierName);
  bool getDocumentationClassAnnotation(QString className);
  QString numProcessors();
  QString help(QString topic);
  QStringList getConfigFlagValidOptions(QString topic, QString *mainDescription = 0, QStringList *descriptions = 0);
  bool setDebugFlags(QString flags);
  bool exportToFigaro(QString className, QString directory, QString database, QString mode, QString options, QString processor);
  bool copyClass(QString className, QString newClassName, QString withIn);
  QStringList getEnumerationLiterals(QString className);
signals:
  void commandFinished();
public slots:
  void logCommand(QString command, QTime *commandTime);
  void logResponse(QString response, QTime *responseTime);
  void showException(QString exception);
  void openOMCLoggerWidget();
  void sendCustomExpression();
};

class CustomExpressionBox : public QLineEdit
{
public:
  CustomExpressionBox(OMCProxy *pOMCProxy);
  OMCProxy *mpOMCProxy;
protected:
  virtual void keyPressEvent(QKeyEvent *event);
};

#endif // OMCPROXY_H
