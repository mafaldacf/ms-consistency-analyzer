package logger

import (
	"fmt"
	"path/filepath"
	"runtime"
	"strings"

	"github.com/sirupsen/logrus"
)

var Logger = logrus.New()

type CustomFormatter struct{}

func (f *CustomFormatter) Format(entry *logrus.Entry) ([]byte, error) {
	var file string
	var line int
	var ok bool
	i := 1
	// just noob and hardcoded stuff here
	for i < 20 {
		_, file, line, ok = runtime.Caller(i)
		if !strings.Contains(file, "entry.go") && !strings.Contains(file, "logger.go") {
			break
		}
		i = i + 1

	}
	if !ok {
		file = "???"
		line = 0
	} else {
		file = filepath.Base(file)
	}
	levelColor := getColor(entry.Level)
	levelText := fmt.Sprintf("\x1b[%dm%-5s\x1b[0m", levelColor, strings.ToUpper(entry.Level.String()[:4]))

	// %-4d forces to have an equal \tab in all lines
	msg := fmt.Sprintf("%s:%-10d \t- %s%s\n", file, line, levelText, entry.Message)
	return []byte(msg), nil
}

func init() {
	Logger.SetLevel(logrus.InfoLevel)
	Logger.SetFormatter(&CustomFormatter{})
}

func getColor(level logrus.Level) int {
	switch level {
	case logrus.DebugLevel:
		return 37 // gray
	case logrus.InfoLevel:
		return 36 // cyan
	case logrus.WarnLevel:
		return 33 // yellow
	case logrus.ErrorLevel:
		return 31 // red
	case logrus.FatalLevel, logrus.PanicLevel:
		return 35 // magenta
	default:
		return 0 // default color
	}
}
