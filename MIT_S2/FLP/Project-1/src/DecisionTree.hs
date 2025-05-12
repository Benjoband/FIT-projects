-- DecisionTree.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Implementation of decision tree with print function

module DecisionTree where

data DecisionTree
  = Leaf String
  | Node Int Double DecisionTree DecisionTree
  deriving (Show, Eq)

-- Print decision tree with indentation
printTree :: DecisionTree -> Int -> IO ()
printTree (Leaf label) indentLevel = do
  putStrLn $ replicate indentLevel ' ' ++ "Leaf: " ++ label
printTree (Node featureIndex threshold left right) indentLevel = do
  putStrLn $ replicate indentLevel ' ' ++ "Node: " ++ show featureIndex ++ ", " ++ show threshold
  printTree left (indentLevel + 2)
  printTree right (indentLevel + 2)