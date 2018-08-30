from dictionary_tree import WordSolver
class CharacterNode:
    def __init__(self, ch):
        """
        tree node of a character
        :param ch: char type character
        """
        self.val = ch
        self.next = {}
        self.is_word = False

    def insert(self, ch):
        """
        insert a character node
        :param ch: next character
        :return: next character node
        """
        if ch not in self.next:
            node = CharacterNode(ch)
            self.next[ch] = node
            return node
        else:
            return self.next[ch]

    def find(self, ch):
        return ch in self.next


class CrosswordSolver:
    def __init__(self, mapMode=False):
        self.mapMode = mapMode
        self.wordTreeRoot = CharacterNode("")

    def _solve(self, i, j, matrix):
        ans = []
        # find word in horizontal order
        cur = self.wordTreeRoot
        string = ""
        for idx in range(j, len(matrix[i])):
            ch = matrix[i][idx]
            string += ch
            if cur.find(ch):
                cur = cur.next[ch]
                if cur.is_word:
                    # find a word
                    ans.append(string)
            else:
                break

        # find word in vertical order
        cur = self.wordTreeRoot
        string = ""
        for idx in range(i, len(matrix)):
            ch = matrix[idx][j]
            string += ch
            if cur.find(ch):
                cur = cur.next[ch]
                if cur.is_word:
                    # find a word
                    ans.append(string)
            else:
                break
        return ans

    def updateWords(self, words):
        words = set(words)
        words = sorted(words)
        for word in words:
            cur = self.wordTreeRoot
            for ch in word:
                cur = cur.insert(ch)
            cur.is_word = True

    def solve(self, charactorMatrix):
        ans = []
        # iter solve point
        # with ProcessPoolExecutor(max_workers=4) as executor:
        #     with Manager() as manager:
        #         matrix = manager.list()
        #         for row in charactorMatrix:
        #             matrix.append(row)
        #         futures = [executor.submit(self._solve, i, j, matrix)
        #                    for i in range(len(charactorMatrix))
        #                    for j in range(len(charactorMatrix[i]))]
        #         for future in as_completed(futures):
        #             ans.extend(future.result())
        for i in range(len(charactorMatrix)):
            for j in range(len(charactorMatrix[i])):
                ans.extend(self._solve(i, j, charactorMatrix))
        return ans


if __name__ == "__main__":
    from time import time
    from random import choice, seed
    import pickle

    with open("words.txt") as fp:
        words = list(line[:-1].lower() for line in fp)
        solver = CrosswordSolver()
        t = time()
        solver.updateWords(words)
        insertTime1 = time() - t

        c_solver = WordSolver()
        t = time()
        for word in words:
            c_solver.insert(word)
        insertTime2 = time() - t

    characters = [chr(_) for _ in range(ord('a'), ord('z') + 1)]

    test = [
        ['m', 'e', 'r'],
        ['a', 'p', 'i'],
        ['y', 'e', 'p']
    ]
    sz = 400
    seed(time())
    test = [[choice(characters) for _ in range(sz)] for _ in range(sz)]

    for row in test:
        print(row)

    t = time()
    ans1 = solver.solve(test)
    solveTime1 = time() - t

    t = time()
    ans2 = c_solver.solve(test)
    solveTime2 = time() - t

    print("ans1 == ans2 is", set(ans1) == set(ans2))
    print("ans1 - ans2 =", set(ans1) - set(ans2))
    print("ans1:", set(ans1))
    print("ans2:", set(ans2))
    print("python insert:", insertTime1, 's', "C insert:", insertTime2, 's')
    print("python solve:", solveTime1, 's', "C solve:", solveTime2, 's')

    # with open("cross_word_solver.dmp", 'wb') as fp:
    #     pickle.dump(solver, fp)
