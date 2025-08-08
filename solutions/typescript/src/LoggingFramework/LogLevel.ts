export enum LogLevelEnum {
  DEBUG, // 0
  INFO, // 1
  WARN, // 2
  ERROR, // 3
  FATAL, // 4
}

export function isAsSevereAs(
  level1: LogLevelEnum,
  level2: LogLevelEnum,
): boolean {
  return level1 >= level2;
}
