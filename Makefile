all:
	@gcc log.c common/array/_/array.c common/string/_/string.c common/memory/_/memory.c http_route.c http_header_parser.c main.c -o main -Wall

run: all
	@./main

clean:
	-rm main

test:
	@gcc log.c http_header_parser.c parse_test.c -o main -Wall