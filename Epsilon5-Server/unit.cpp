#include "unit.h"

TUnit::TUnit(ETeam team, const TObjectParams& params, QObject* parent)
    : TObject(params, parent)
    , Team(team)
{
}
