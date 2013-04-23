#!/usr/bin/env ruby
#
# Maria Deslis
# csci403 - Bakos - spring 2013
#
require 'rubygems'
require 'mongo'

include Mongo

DB_URL = "mongodb://<user>:<password>@staff.mongohq.com:10033/zoolicious"

#List Zoos
def list_zoos(db)
	zoos = db["zoos"]
	i = 1
	zoos.find.each do |zoo|
		puts "#{i}, #{zoo["name"]}"
		i = i + 1
	end
end

#List Habitats
def list_habitats(db)
	habitats = db["habitats"]
	i = 1
	habitats.find.each do |habitat|
		puts "#{i}, Name: #{habitat["name"]}"
		puts "\tCapacity: #{habitat["capacity"]}"
		puts "\tDescription: #{habitat["description"]}"
		puts "\tLocation #{habitat["location"]}"
		i = i + 1
	end
end

#List Animals
def list_animals(db)
	animals = db["animals"]
	habitats = db["habitats"]
	animals.find.each do |animal|
		puts "Name: #{animal["name"]}"
		puts "\tDescription: #{animal["description"]}" unless animal["description"] == nil
		puts "\tCuteness: #{animal["cuteness"]}" unless animal["cuteness"] == nil
		habitat = habitats.find_one("_id" => animal["habitat_id"]) unless animal["habitat_id"] == nil
		puts "\tHabitat: #{habitat["name"]}" unless habitat == nil
	end
end

#Add Animal
def add_animal(db)
	animals = db["animals"]
	add_animal = ""
	add_descrip = ""
	add_cuteness = ""
	add_habitat = ""

	while (add_animal.empty?)
		puts "What animal are we adding?"
		add_animal = gets.chomp
	end

	while (add_descrip.empty?)
		puts "Please describe the animal"
		add_descrip = gets.chomp
	end

	while (add_cuteness.empty?)
		puts "Please give cuteness rating"
		add_cuteness = gets.chomp
	end

	animals.insert({ :name => add_animal, :description => add_descrip, :cuteness => add_cuteness})
end

def main_menu
	puts "\nMain Menu"
	puts "A. List Zoos"
	puts "B. Lists Habitats"
	puts "C. List Animals"
	puts "D. Add Animal"
	puts "Q. Quit"
end

def execute_choice(choice)
	db = MongoClient.new("staff.mongohq.com", 10033).db("zoolicious")
	db.authenticate("csci403", "wuwnosql403")

	case choice
	when "A", "a"
		puts "\nListing Zoos"
		list_zoos(db)
	when "B", "b"
		puts "\nListing Habitats"
		list_habitats(db)
	when "C", "c"
		puts "\nListing Animals"
		list_animals(db)
	when "D", "d"
		puts "\nAdd Animal"
		add_animal(db)
	when "Q"
		puts "Exiting..."
	else
		puts "Sorry, that option is not available"
	end
end

choice = nil
puts "ZOOLICIOUS BABY!"
while (choice != 'Q')
	main_menu
	execute_choice(choice = gets.chomp!)
end
