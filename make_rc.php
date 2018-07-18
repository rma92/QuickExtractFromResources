<?php
$dir_name = "files";
$file_count = 0;
$start_res_id = 101;
$res_id = $start_res_id;
$file_name_str = "";
$rc_file_contents = "100 RCDATA rc_files_temp.txt\n";

$d = scandir( $dir_name );

foreach( $d as $f )
{
  if( $f != '.' && $f != '..' )
  {
    $rc_file_contents .= $res_id. " RCDATA ". "\"$dir_name\\\\$f\"\r\n";
    $file_name_str .= $f . "\n";
    echo $f, "\n";
    ++$res_id;
    ++$file_count;
  }
}
$file_name_str = $file_count . "\n" . $file_name_str;
file_put_contents( "rc_files_temp.txt", $file_name_str );
echo $rc_file_contents;
file_put_contents( "rc_temp.rc", $rc_file_contents );
?>
