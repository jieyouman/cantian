CREATE TABLE SYS_GARBAGE_TABLES
(
  UID            BINARY_INTEGER       NOT   NULL,
  TAB_NAME       VARCHAR(64)          NOT   NULL
) SYSTEM 1044 TABLESPACE SYSTEM
/

CREATE UNIQUE INDEX IX_GARBAGE_TABLE_001 ON SYS_GARBAGE_TABLES(UID, TAB_NAME) TABLESPACE SYSTEM
/