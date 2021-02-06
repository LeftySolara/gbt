--
-- File generated with SQLiteStudio v3.2.1 on Fri Feb 5 17:47:02 2021
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: meta
DROP TABLE IF EXISTS meta;

CREATE TABLE meta (
    gbt_version_major INT NOT NULL
                          DEFAULT (0),
    gbt_version_minor INT NOT NULL
                          DEFAULT (0),
    gbt_version_patch INT DEFAULT (0) 
                          NOT NULL
);

INSERT INTO meta (gbt_version_major, gbt_version_minor, gbt_version_patch) VALUES (0, 0, 1);

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
PRAGMA user_version = 0;
