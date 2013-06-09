#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "map.h"

#include <QLabel>

const int TILE_SIZE = 100;

TMap::TMap(QObject* parent)
    : QObject(parent)
    , Width(0)
    , Height(0)
    , Loaded(false)
    , WHRatio(QPointF(1.0, 1.0))
{
}

void TMap::LoadMap(const QString& map) {
    USettings settings;
    settings.Load("maps/" + map + "/config.ini");
    QString color = settings.GetParameter("color");
    Color = QColor(color);
    Width = settings.GetParameter("width");
    Height = settings.GetParameter("height");
    LoadTiles();
    makeBackgroundImage();
    Loaded = true;
    WHRatio = QPointF(1.0, 1.0);
    if( Width && Height ) {
        // 1.0 means max size, other always less than 1
        WHRatio = QPointF(Width > Height ?  1.0 : (qreal)Width / Height,
                          Width > Height ? (qreal)Height / Width : 1.0);
    }
}

void TMap::makeBackgroundImage()
{
  QVector<ETerrain> terrain = loadTerrainMap();
  Background = new QPixmap(Width, Height);
  QRect rect(0, 0, TILE_SIZE, TILE_SIZE);
  QPainter painter(Background);
  for (size_t y = 0; y < Height; y += TILE_SIZE)
    for (size_t x = 0; x < Width; x += TILE_SIZE)
    {
      size_t index = (y / TILE_SIZE ) * (Width / TILE_SIZE) + (x / TILE_SIZE);
      rect.moveTo(x, y);
      painter.fillRect(rect, Qt::green);
      painter.drawPixmap(rect, Images[terrain[index]]);
    }
  Background->save("Pixmap.jpeg");
}

ETerrain ToTerrainType(const QString& str)
{
  if (str == "water") return T_Water;
  if (str == "dirt") return T_Dirt;
  else throw UException("Unknown terrain requested");
}

QVector<ETerrain> TMap::loadTerrainMap()
{
  QString fileName("maps/tdm_fort/terrains.txt");
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      throw UException("Error opening " + fileName);
  }
  QTextStream in(&file);
  QString line = "";

  while ((line = in.readLine()) != "%%") {
    if (line.isEmpty() || line[0] == '#') {
      continue;
    }
    QStringList size = line.split(":");
  }

  QMap<QString, ETerrain> terrainMap;
  line = "";
  while ((line = in.readLine()) != "%%") {
    if (line.isEmpty() || line[0] == '#') {
      continue;
    }
    QStringList defs = line.split(":");
    ETerrain terrain = ToTerrainType(defs[1]);
    terrainMap.insert(defs[0], terrain);
  }

  QVector<ETerrain> terrain;
  line = "";
  while (!in.atEnd()) {
    line = in.readLine();
    if (line.isEmpty() || line[0] == '#') {
      continue;
    }
    QStringList row = line.split(":");
    for (const QString& id : row)
      terrain.append(terrainMap[id]);
  }
  return terrain;
}

void TMap::LoadTiles()
{
  const QString imagesDir("maps/tdm_fort/images/");
  QString tiles[] {"water", "dirt"};
  for (const QString& tile : tiles)
  {
    QPixmap tilePix;
    qDebug() << tilePix.load(imagesDir + tile + ".jpeg");
    Images.insert(ToTerrainType(tile), tilePix);
  }
}

TMap::~TMap() {
    if (Background) {
        delete Background;
    }
}

void TMap::DrawBackground(const QPoint& playerPos, const QSize& frameSize, QPainter& painter) {
    if (!Loaded) {
        throw UException("Map not loaded!");
    }
    int centerX = Background->width() / 2;
    int centerY = Background->height() / 2;
    int newPekaPosX = centerX + playerPos.x();
    int newPekaPosY = centerY + playerPos.y();
    int cutX = newPekaPosX - frameSize.width() / 2;
    int cutY = newPekaPosY - frameSize.height() / 2;
    painter.fillRect(0, 0, frameSize.width(), frameSize.height(), Color);
    painter.drawPixmap(-cutX, -cutY, *Background);
}

size_t TMap::GetWidth()
{
    return Width;
}

size_t TMap::GetHeight()
{
    return Height;
}

QSize TMap::GetMinimapSize(quint8 maxMinimapSize)
{
    return QSize(maxMinimapSize * WHRatio.x(), maxMinimapSize * WHRatio.y());
}

QPoint TMap::GetObjectPosOnMinimap(int objectPosX, int objectPosY, quint8 maxMinimapSize)
{
    return QPoint(
        ((qreal)objectPosX / Width + 0.5) * maxMinimapSize * WHRatio.x(),
        ((qreal)objectPosY / Height + 0.5) * maxMinimapSize * WHRatio.y());
}

QPoint TMap::GetObjectPosOnMinimap(QPoint objectPos, quint8 maxMinimapSize)
{
    return GetObjectPosOnMinimap(objectPos.x(), objectPos.y(), maxMinimapSize);
}
