#!/usr/bin/env ruby

if ARGV.length != 1 then
    puts "Usage: randomline.rb <num_nodes>"
    exit 1
end

n = ARGV[0].to_i
puts "#{n} #{n-1}"
a = (0..n-1).to_a.shuffle
a.each_index do |i|
    if a[i+1] then
        puts "#{a[i]} #{a[i+1]}"
    end
end

exit 0
