--
-- File generated with SQLiteStudio v3.2.1 on Fri Sep 6 16:11:34 2019
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: games
DROP TABLE IF EXISTS games;

CREATE TABLE games (
    id          INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                        NOT NULL
                        DEFAULT (0),
    name        TEXT    NOT NULL ON CONFLICT ROLLBACK,
    status_id   INT     REFERENCES status (id),
    series_id   INT     REFERENCES series (id),
    platform_id INT     REFERENCES platforms (id),
    genre_id    INT     REFERENCES genres (id)
);

INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (1, 'Animal Crossing: New Leaf', 1, 1, 1, 1);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (2, 'Yakuza 0', 1, 2, 2, 2);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (4, 'Animal Crossing: New Horizons', 0, 1, 3, 1);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (5, 'Monster Hunter: World', 3, 3, 2, 3);
INSERT INTO games (id, name, status_id, series_id, platform_id, genre_id) VALUES (6, 'Monster Hunter Generations Ultimate', 1, 3, 3, 3);

-- Table: genres
DROP TABLE IF EXISTS genres;

CREATE TABLE genres (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
);

INSERT INTO genres (id, name) VALUES (-1, NULL);
INSERT INTO genres (id, name) VALUES (1, 'Simulation');
INSERT INTO genres (id, name) VALUES (2, 'Action/Adventure');
INSERT INTO genres (id, name) VALUES (3, 'Action');

-- Table: platforms
DROP TABLE IF EXISTS platforms;

CREATE TABLE platforms (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
);

INSERT INTO platforms (id, name) VALUES (-1, NULL);
INSERT INTO platforms (id, name) VALUES (1, 'Nintendo 3DS');
INSERT INTO platforms (id, name) VALUES (2, 'PC');
INSERT INTO platforms (id, name) VALUES (3, 'Nintendo Switch');

-- Table: series
DROP TABLE IF EXISTS series;

CREATE TABLE series (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
);

INSERT INTO series (id, name) VALUES (-1, NULL);
INSERT INTO series (id, name) VALUES (1, 'Animal Crossing');
INSERT INTO series (id, name) VALUES (2, 'Yakuza');
INSERT INTO series (id, name) VALUES (3, 'Monster Hunter');

-- Table: status
DROP TABLE IF EXISTS status;

CREATE TABLE status (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name         UNIQUE ON CONFLICT ROLLBACK
);

INSERT INTO status (id, name) VALUES (-1, NULL);
INSERT INTO status (id, name) VALUES (0, 'Not Started');
INSERT INTO status (id, name) VALUES (1, 'Playing');
INSERT INTO status (id, name) VALUES (2, 'Finished');
INSERT INTO status (id, name) VALUES (3, 'On Hold');
INSERT INTO status (id, name) VALUES (4, 'Dropped');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
