-- ParseTree.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Implementation of parsing of decision tree from file

module ParseTree where

import Data.Char (isSpace)
import Data.List (stripPrefix)
import DecisionTree

-- Recursively processes lines, constructing the tree.
parseTree :: [String] -> Int -> (DecisionTree, [String])
parseTree [] _ = error "Unexpected end of file"
parseTree (line : rest) indentLevel =
  case parseNodeOrLeaf line of
    Just (Leaf classLabel, lineIndent)
      | lineIndent == indentLevel -> (Leaf classLabel, rest)
      | otherwise -> error "Incorrect indentation"
    Just (Node feature threshold _ _, lineIndent)
      | lineIndent == indentLevel ->
          let (leftSubtree, rest1) = parseTree rest (indentLevel + 2)
              (rightSubtree, rest2) = parseTree rest1 (indentLevel + 2)
           in (Node feature threshold leftSubtree rightSubtree, rest2)
      | otherwise -> error "Incorrect indentation"
    Nothing -> error $ "Invalid line format: " ++ line

-- Determines if a line is a Node or a Leaf.
parseNodeOrLeaf :: String -> Maybe (DecisionTree, Int)
parseNodeOrLeaf line
  | Just rest <- stripPrefix "Node: " (dropWhile isSpace line) =
      case span (/= ',') rest of
        (featureStr, ',' : thresholdStr) ->
          case (reads featureStr :: [(Int, String)], reads thresholdStr :: [(Double, String)]) of
            ([(feature, "")], [(threshold, "")]) ->
              Just (Node feature threshold (Leaf "") (Leaf ""), countIndent line)
            _ -> Nothing
        _ -> Nothing
  | Just rest <- stripPrefix "Leaf: " (dropWhile isSpace line) =
      Just (Leaf (dropWhile isSpace rest), countIndent line)
  | otherwise = Nothing

-- Counts indent of line
countIndent :: String -> Int
countIndent = length . takeWhile isSpace

-- Reads the file, splits into lines, and calls parseTree.
parseTreeFromFile :: FilePath -> IO DecisionTree
parseTreeFromFile filePath = do
  content <- readFile filePath
  let linesOfFile = lines content
  case parseTree linesOfFile 0 of
    (tree, _) -> return tree