-- Cart.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Implementation of CART

module Cart where

import Data.List
import DecisionTree
import TrainingData

-- Compute Gini index from samples
giniIndex :: [LabeledSample] -> Double
giniIndex samples
  | null samples = 0.0
  | otherwise =
      let total = fromIntegral (length samples)
          labels = map snd samples
          uniqueLabels = nub labels
          probabilities = [fromIntegral (count l labels) / total | l <- uniqueLabels]
       in 1.0 - sum (map (^ (2 :: Int)) probabilities)

-- Count occurrences of an item in a list
count :: (Eq a) => a -> [a] -> Int
count _ [] = 0
count x (y : ys)
  | x == y = 1 + count x ys
  | otherwise = count x ys

-- Split samples into two sets based on a feature index and threshold
splitSamples :: Int -> Double -> [LabeledSample] -> ([LabeledSample], [LabeledSample])
splitSamples featureIndex threshold =
  partition (\(features, _) -> featureIndex < length features && features !! featureIndex <= threshold)

-- Generate thresholds for a feature
generateThresholds :: Int -> [LabeledSample] -> [Double]
generateThresholds featureIndex samples =
  let sorted = sort . nub $ [features !! featureIndex | (features, _) <- samples, featureIndex < length features]
   in zipWith (\a b -> (a + b) / 2) (init sorted) (tail sorted)

-- Find the best split for a feature
bestSplitForFeature :: Int -> [LabeledSample] -> Maybe (Double, Double, [LabeledSample], [LabeledSample])
bestSplitForFeature featureIndex samples =
  let thresholds = generateThresholds featureIndex samples
      n = fromIntegral (length samples)
      candidates =
        [ let (left, right) = splitSamples featureIndex t samples
              giniL = giniIndex left
              giniR = giniIndex right
              nl = fromIntegral (length left)
              nr = fromIntegral (length right)
              score = (nl / n) * giniL + (nr / n) * giniR
           in (score, t, left, right)
          | t <- thresholds
        ]
   in case candidates of
        [] -> Nothing
        _ ->
          let (bestScore, bestThreshold, bestLeft, bestRight) = minimum candidates
           in Just (bestThreshold, bestScore, bestLeft, bestRight)

-- Find the best split across all features
findBestSplit :: [LabeledSample] -> Maybe (Int, Double, [LabeledSample], [LabeledSample])
findBestSplit [] = Nothing
findBestSplit samples =
  let featureCount = length (fst (head samples)) -- Get the number of features
      results = concatMap (evaluateFeatureSplit samples) [0 .. featureCount - 1]
   in selectBestSplit results

-- Evaluate the best split for a single feature
evaluateFeatureSplit :: [LabeledSample] -> Int -> [(Double, Int, Double, [LabeledSample], [LabeledSample])]
evaluateFeatureSplit samples featureIndex =
  case bestSplitForFeature featureIndex samples of
    Just (threshold, score, left, right) -> [(score, featureIndex, threshold, left, right)]
    Nothing -> []

-- Select the best split from the list of results
selectBestSplit :: [(Double, Int, Double, [LabeledSample], [LabeledSample])] -> Maybe (Int, Double, [LabeledSample], [LabeledSample])
selectBestSplit [] = Nothing
selectBestSplit results =
  let (_, bestFeature, bestThreshold, bestLeft, bestRight) = minimum results
   in Just (bestFeature, bestThreshold, bestLeft, bestRight)

-- Recursive tree construction
createTreeFromSamples :: [LabeledSample] -> DecisionTree
createTreeFromSamples samples =
  case allSameLabel samples of
    Just lbl -> Leaf lbl
    Nothing ->
      case findBestSplit samples of
        Just (featureIdx, threshold, leftSet, rightSet) ->
          Node
            featureIdx
            threshold
            (createTreeFromSamples leftSet)
            (createTreeFromSamples rightSet)
        Nothing -> Leaf (majorityLabel samples)

-- Check if all samples have the same label -> just one class
allSameLabel :: [LabeledSample] -> Maybe String
allSameLabel [] = Nothing
allSameLabel ((_, l) : xs)
  | all (\(_, lbl) -> lbl == l) xs = Just l
  | otherwise = Nothing

-- Find the majority label in the sample
majorityLabel :: [LabeledSample] -> String
majorityLabel samples =
  snd $ maximum [(countLabel lbl, lbl) | lbl <- labels]
  where
    labels = map snd samples
    countLabel lbl = length (filter (== lbl) labels)