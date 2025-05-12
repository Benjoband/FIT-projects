-- Helpers.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Implementation of helper functions

module Helpers where

-- Split string by a delimiter
splitBy :: Char -> String -> [String]
splitBy _ [] = [""]
splitBy delimiter (c : cs)
  | c == '\n' = "" : splitBy delimiter cs
  | c == delimiter = "" : splitBy delimiter cs
  | otherwise =
      case splitBy delimiter cs of
        [] -> [[c]] -- empty list
        (x : xs) -> (c : x) : xs