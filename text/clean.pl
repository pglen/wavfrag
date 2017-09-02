#! /usr/bin/perl
####################################################################
###
### script name : fixcmudict.pl
### version: 0.1
### created by: Ken MacLean
### mail: contact@voxforge.org
### Date: 2006.7.25
### Command: perl ./fixcmudict.pl [infile-cmudict] [outfile-lexicon]
###   
### Copyright (C) 2006 Ken MacLean
###
### This program is free software; you can redistribute it and/or
### modify it under the terms of the GNU General Public License
### as published by the Free Software Foundation; either version 2
### of the License, or (at your option) any later version.
###
### This program is distributed in the hope that it will be useful,
### but WITHOUT ANY WARRANTY; without even the implied warranty of
### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
### GNU General Public License for more details.
###                                                              
####################################################################

#use strict;

if ($#ARGV != 1) {
 print "usage: inputfilename outputfilename\n";
 exit;
}
$inputfilename = $ARGV[0];
$outputfilename = $ARGV[1];
open(FILEIN, "<$inputfilename") or die ("need input file name"); # open for input
open(FILEOUT, ">$outputfilename") or die ("need output file name"); # open for output
#print "sorting:";print $inputfilename; print " to:";print "$outputfilename \n";

$cnt = 0;
$oldword;  

while ($line = <FILEIN>) {
 
 $line_back = $line;

 chomp($line);
 
  @entry = split(/ +/,$line);
  #print "$line\n"; 
  $word = shift(@entry);
  # optional entry killed automatically
  if($line =~ m/\[/)
	{
	$word2 = shift(@entry);
	}
  my $idx = 0;

 #// Convert all to lower case  
 foreach $aa (@entry)
 {
	$aa = uc($aa);
	#print $aa . " ";
 }
 
$word = uc($word);
 
$space = "";
 for($loop = 0; $loop < 20 - length($word); $loop++)
	{
	$space .= " ";
	}
	
if($word ne $oldword)
	{
	print FILEOUT "$word $space @entry\n"; 
	}
else
	{
	#	print "not  " . $word . " " . $oldword . "\n";
	}
	
$oldword = $word;
  
  if($cnt++ > 40)
	{
	#last;
	}
}
  
close(FILEIN);
close(FILEOUT);
