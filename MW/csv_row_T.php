<?php

require("/var/www/MW/csv_row.inc");

$row = new csv_row;
print_r($row);

$row->push('data1');
print_r($row);
$row->push('da"ta2');
$row->push('data""3"');
print_r($row);

print $row->get_string();
