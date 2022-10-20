#!/usr/bin/perl

@ARGV = ("-") unless @ARGV;

$count = 0;

print "Perl\n";
print "Processing $ARGV[0] ...\n";

open(TXT, $ARGV[0]) or die "Failed to open $ARGV[0]: $!\n";

%wc = ();

for $line (<TXT>) {
    $count++;

    # Remove \n$
    chomp($line);
    #if (length($line) == 0) {
    #    next;
    #}

    for $word (split(/ /, $line)) {
        $wc{$word}++;
    }
}

close(TXT);

print "Processed $count lines.\n";

for $i (sort { $wc{$b} <=> $wc{$a} } keys %wc) {
    printf("%10d: [%s]\n", $wc{$i}, $i);
}
