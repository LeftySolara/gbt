/******************************************************************************
 * library.cpp : Object for managing the user's game library
 * ****************************************************************************
 * Copyright (C) 2021 Jalen Adams
 *
 * Authors: Jalen Adams <jalen@jalenkadams.me>
 *
 * This file is part of gbt.
 *
 * gbt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gbt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gbt.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "gbt/library.h"
#include "gbt/log.h"

/**
 * @brief Constructs a new Library instance.
 */
Library::Library()
{
    game_table_model_ptr.reset(new GameTableModel());
    game_table_model_ptr->setTable("game");
    game_table_model_ptr->select();
}

/**
 * @brief Gets the database model of the library.
 */
GameTableModel *Library::getModel() const
{
    return game_table_model_ptr.get();
}

/**
 * @brief Adds a new game to the library.
 * @param title The title of the game.
 * @return true if the game is added successfuly, false otherwise
 */
bool Library::addGame(QString title)
{
    if (!game_table_model_ptr->addGame(title)) {
        qCWarning(LOG_GBT) << "ERROR: Unable to add game to library.";
        return false;
    }
    return true;
}

/**
 * @brief Removes a game from the library.
 * @param id The ID of the game to remove.
 * @return true if the game is removed successfully, false otherwise.
 */
bool Library::removeGame(const unsigned int id)
{
    if (!game_table_model_ptr->removeGame(id)) {
        qCWarning(LOG_GBT) << "ERROR: Unable to remove game from library.";
        return false;
    }
    return true;
}
