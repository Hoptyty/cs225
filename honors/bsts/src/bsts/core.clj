(ns bsts.core)

(defrecord Node [left key value right])

(defn add 
  "Adds key `k` and value `v` to tree `bst`."
  [bst k v]
  (cond (nil? bst) (Node. nil k v nil)
        (> 0 (compare k (:key bst))) (Node. (add (:left bst) k v)
                                   (:key bst)
                                   (:value bst)
                                   (:right bst))
        :else  (Node. (:left bst)
                      (:key bst)
                      (:value bst)
                      (add (:right bst) k v)) ) )

(defn make-tree
  "We may want to change the representation of this later."
  []
  nil)

(defn show [bst]
  (cond (nil? bst) " x "
        (and (nil? (:left bst))
             (nil? (:right bst)))  (str " " (:key bst) "/" (:value bst) " ")
        :otherwise (str "(" (:key bst) "/" (:value bst) " " (show (:left bst)) " " 
                        (show (:right bst)) ")"))) 

(defn find [bst desire]
  (cond (nil? bst) nil
        (= desire (:key bst)) (:value bst)
        (> 0 (compare desire (:key bst))) (find (:left bst) desire)
        :else (find (:right bst) desire) ))


(defn size
  "Return the number of nodes in a BST."
  [bst]
  (if (nil? bst) 0
	 (+ 1 (size (:left bst)) (size (:right bst)))))

(defn rightMost [bst]
  (if (nil? (:right bst)) bst
      (rightMost (:right bst))))

(defn twoChild [bst k]
  (cond (nil? bst) nil
	(= (:key bst) k) (if (nil? (:left bst)) nil (:left bst))
	:else (Node. (twoChild (:left bst) k)
		     (:key bst)
		     (:value bst)
		     (twoChild (:right bst) k))))				  	   
		     
(defn doRemove [bst]
  (cond  (and (nil? (:left bst)) (nil? (:right bst))) nil
         (nil? (:left bst))  (:right bst)
         (nil? (:right bst)) (:left bst)
	 :else (Node. (twoChild (:left bst) (:key (rightMost (:left bst))))
		      (:key (rightMost (:left bst)))
		      (:value (rightMost (:left bst)))
		      (twoChild (:right bst) (:key (rightMost (:left bst)))))))	


(defn delete 
  "Deletes the node with `victim` as its key."
  [bst victim]
  (cond (nil? bst) nil
	(= victim (:key bst)) (doRemove bst)
	(> 0 (compare victim (:key bst))) (Node. (delete (:left bst) victim)
						 (:key bst)
						 (:value bst)
						 (:right bst))
	:else (Node. (:left bst)
		     (:key bst)
		     (:value bst)
		     (delete (:right bst) victim))))

