#ifndef SIMILAR_H
#define SIMILAR_H

#include "game.h"
#include <string>
#include <utility>
#include <vector>

/**
 * function for comparing two games to see if they are similar
 * tolerance should be between 0 and 1 and the higher it is the less likely
 * two games will be similar. Use tolerance between 0.5 and 0.8.
 * Use 0.5 threshold for less strict (more similar games for each game).
 * Use 0.8 threshold for more strict (less similar games for each game).
 */
bool gamesSimilar(const Game &game1, const Game &game2, float threshold);

#endif // SIMILAR_H
