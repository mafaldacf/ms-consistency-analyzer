package postnotification

import "strconv"

func Int64ToString(i int64) string {
    return strconv.FormatInt(i, 10)
}

func StringToInt64(s string) (int64, error) {
    // Parse the string into an int64 with base 10
    num, err := strconv.ParseInt(s, 10, 64)
    if err != nil {
        return 0, err
    }
    return num, nil
}
