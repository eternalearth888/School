#!/usr/bin/env ruby
#
# Maria Deslis
# csci403 - Bakos - spring 2013
#

require 'redis'

redis = Redis.new(:host => "pub-redis-13059.us-west-1.1.azure.garantiadata.com", :port => 13059, :password => "wuwnosql403")

puts "1: AUTH"
puts redis.AUTH("wuwnosql403")

puts "\n2: SET server:name \"test\""
puts redis.SET("test", "Hello World")

puts "\n3: GET server:name"
puts redis.GET("test")

puts "\n4: SET connections 10"
puts redis.SET("test", 10)

puts "\n5: INCR connections"
puts redis.INCR("test")

puts "\n6: DEL connections"
puts redis.del("test")

puts "\n7: RPUSH senshi \"Saturn\""
puts redis.RPUSH("senshi", "Saturn")
puts "RPUSH senshi \"Uranus\""
puts redis.RPUSH("senshi", "Uranus")

puts "\n8: LPUSH senshi \"Pluto\""
puts redis.LPUSH("senshi", "Pluto")

puts "\n9: LRANGE senshi 0 -1"
puts redis.LRANGE("senshi", 0, -1)

puts "\n10: LLEN senshi"
puts redis.LLEN("senshi")

puts "\n11: LPOP senshi"
puts redis.LPOP("senshi")

puts "\n12: RPOP senshi"
puts redis.RPOP("senshi")

puts "\n13: DEL senshi"
puts redis.DEL("senshi")

puts "\n14: SADD designers \"CHANEL\""
puts redis.SADD("designers", "CHANEL")
puts "SADD designers \"Yves Saint Laurent\""
puts redis.SADD("designers", "Yves Saint Laurent")
puts "SADD designers \"Gucci\""
puts redis.SADD("designers", "Gucci")

puts "\n15: SREM designers \"Gucci\""
puts redis.srem("designers", "Gucci")

puts "\n16: SISMEMBER designers \"CHANEL\""
puts redis.SISMEMBER("designers", "CHANEL")
puts "SISMEMBER designers \"Gucci\""
puts redis.SISMEMBER("designers", "Gucci")

puts "\n17: SMEMBERS designers"
puts redis.SMEMBERS("designers")

puts "SADD artists \"Picasso\""
puts redis.SADD("artists", "Picasso")

puts "\n18: SUNION designers artists"
puts redis.SUNION("designers", "artists")

puts "DEL designers"
redis.DEL("designers")

puts "DEL artists"
redis.DEL("artists")

puts "\n19: ZADD howmanytoday 3 \"Heineken\""
puts redis.ZADD("howmanytoday", 3, "Heineken")
puts "ZADD howmanytoday 1 \"ABSOLUT Mandarin\""
puts redis.ZADD("howmanytoday", 1, "ABSOLUT Mandarin")
puts "ZADD howmanytoday 5 \"Green Tea\""
puts redis.ZADD("howmanytoday", 5, "Green Tea")

puts "\n20: ZRANGE howmanytoday 0 -1"
puts redis.ZRANGE("howmanytoday", 0 , -1)

puts "DEL howmanytoday"
redis.DEL("howmanytoday")