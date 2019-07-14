--
-- File generated with SQLiteStudio v3.2.1 on Sun Jul 14 16:25:32 2019
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


-- Table: genres
DROP TABLE IF EXISTS genres;

CREATE TABLE genres (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);


-- Table: platforms
DROP TABLE IF EXISTS platforms;

CREATE TABLE platforms (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);


-- Table: series
DROP TABLE IF EXISTS series;

CREATE TABLE series (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name TEXT    UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);


-- Table: status
DROP TABLE IF EXISTS status;

CREATE TABLE status (
    id   INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                 NOT NULL ON CONFLICT ROLLBACK
                 DEFAULT (0),
    name         UNIQUE ON CONFLICT ROLLBACK
                 NOT NULL ON CONFLICT ROLLBACK
);


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
