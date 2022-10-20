package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

/*
func main() {
	var chars, words, lines int
	r := bufio.NewReader(os.Stdin)
	for {
		switch s, ok := r.ReadString('\n'); {
		case ok != nil:
			fmt.Printf("%d %d %d\n", chars, words, lines)
			return
		default:
			chars += len(s)
			words += len(strings.Fields(s))
			lines++
		}
	}
}
*/

func main() {
	file := os.Args[1]
	fmt.Printf("Processing %s ...\n", file)

	var words = make(map[string]int)

	fp, ok := os.Open(file)
	if ok != nil {
		fmt.Errorf("Failed to open %s", file)
		return
	}

	r := bufio.NewReader(fp)
	count := 0

for_loop:
	for {
		switch line, ok := r.ReadString('\n'); {
		case ok != nil:
			break for_loop
		default:
			for _, word := range strings.Fields(line) {
				words[word]++
			}
		}
		count++
	}

	fmt.Printf("Processed %d lines.\n", count)

	keys := make([]string, 0, len(words))
	for key := range words {
		keys = append(keys, key)
	}
	// Sort by keys
	// sort.Strings(keys)

	// Sort by values
	sort.Slice(keys, func(i, j int) bool {
		return words[keys[i]] > words[keys[j]]
	})

	for _, key := range keys {
		fmt.Printf("%10d: [%s]\n", words[key], key)
	}
}
