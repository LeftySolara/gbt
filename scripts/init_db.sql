--
-- File generated with SQLiteStudio v3.2.1 on Thu May 30 17:30:02 2019
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: games
DROP TABLE IF EXISTS games;

CREATE TABLE games (
    id        INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT
                      NOT NULL
                      DEFAULT (0),
    name      TEXT    NOT NULL ON CONFLICT ROLLBACK,
    status_id INT     REFERENCES status (id),
    series_id INT     REFERENCES series (id)
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

INSERT INTO status (id, name) VALUES (0, 'Not Started');
INSERT INTO status (id, name) VALUES (1, 'Playing');
INSERT INTO status (id, name) VALUES (2, 'Finished');
INSERT INTO status (id, name) VALUES (3, 'On Hold');
INSERT INTO status (id, name) VALUES (4, 'Dropped');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;