#!/usr/bin/ruby

txt = ARGV[0]

puts "Ruby"
printf("Processing %s ...\n", txt)

fp = File.open(txt)

count = 0
wc = Hash.new { |h,k| h[k] = 0 }

fp.each do |line|
    count += 1
    #line.split(/ |\.|,|;|\-/).each { |word|
    line.split().each do |word|
        next if word == "\n"
        wc[word] += 1
    end
end

fp.close()

printf("Processed %d lines.\n", count)

#wc.sort_by{|k,v|v}.reverse().each{ |k, v| printf("%10d: [%s]\n", v, k) }

