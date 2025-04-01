package loggingframework

import (
	"database/sql"
	"fmt"
)

type DatabaseAppender struct {
	db *sql.DB
}

func NewDatabaseAppender(jdbcURL, username, password string) (*DatabaseAppender, error) {
	db, err := sql.Open("mysql", fmt.Sprintf("%s:%s@%s", username, password, jdbcURL))
	if err != nil {
		return nil, err
	}

	return &DatabaseAppender{
		db: db,
	}, nil
}

func (a *DatabaseAppender) Append(message *LogMessage) error {
	stmt, err := a.db.Prepare("INSERT INTO logs (level, message, timestamp) VALUES (?, ?, ?)")
	if err != nil {
		return err
	}
	defer stmt.Close()

	_, err = stmt.Exec(message.Level.String(), message.Message, message.Timestamp)
	return err
}
