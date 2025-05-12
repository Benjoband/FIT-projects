<?php
ini_set('display_errors', 'stderr');
$output = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
/*
    ARGUMENT OPERATIONS
*/

if($argc > 1)
{
    if($argv[1] == "--help" && $argc == 2)
    {
        echo "---NAPOVEDA KE SKRIPTU---";
        echo "UCEL - Cte IPPcode23 ze stdin a na stdout vypisuje reprezentaci v XML";
        echo "moznosti: -- help - vypise help";
        exit(0);
    }
    for($i = 0; $i < $argc; $i++)
    {
        if($argv[1] == "--help")
        {
            exit(10);
        }
    }
}

/*
    HEADER SEARCHING
*/

$header = 0;
while($header == 0)
{
    $input_string = fgets(STDIN);
    if($input_string == false)
        exit(21); // EOF
    $input_string = delete_comments($input_string);
    $input_string = trim($input_string);
    if(strtoupper($input_string) == ".IPPCODE23")
    {
        $header = 1;
        break; // found head
    }
    else if(ctype_space($input_string) == true || $input_string == "")
    {
        continue; // empty line
    }
    else
    {
        exit(21); // something before head
    }
}

$output = add_to_output($output, "<program language=\"IPPcode23\">");

/*
    CODE READING
*/
$instruction_num = 0;
while($input_string = fgets(STDIN))
{
    $line = process_line($input_string);
    if($line == "")
        continue; 
    if($line ==  false)
        break;
    $instruction_num++;
    $instruction_part = explode(" ", $line);
    $ip_count = count($instruction_part);
    $instruction = strtoupper($instruction_part[0]);
    $arg_type = array("","","");
    switch($instruction)
    {
        // <NOTHING>
        case "CREATEFRAME":
        case "PUSHFRAME":
        case "POPFRAME":
        case "RETURN":
        case "BREAK":
            if($ip_count != 1)
                exit(23);
            else
            {
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array());
            }
            break;
        // <var>
        case "DEFVAR":
        case "POPS":
            $arg_type[0] = "var";
            if($ip_count != 2)
            {
                exit(23);
            }
            else if(!is_var($instruction_part[1]))
            {
                exit(23);
            }
            else
            {
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array($instruction_part[1]));
            }
            break;
        
        // <label>
        case "CALL":
        case "LABEL":
        case "JUMP":
            $arg_type[0] = "label";
            if($ip_count != 2)
                exit(23);
            else if(!is_label($instruction_part[1]))
                exit(23);
            else
            {
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array($instruction_part[1]));
            }
            break;

        // <symb>
        case "PUSHS": 
        case "WRITE":
        case "EXIT":
        case "DPRINT":
            if($ip_count != 2)
                exit(23);
            else if(is_symbol($instruction_part[1]))
            {
                if(is_var($instruction_part[1]))
                {
                    $arg_type[0] = "var";
                }
                else
                {
                    $symb = explode("@", $instruction_part[1]);
                    $arg_type[0] = $symb[0];
                    $instruction_part[1] = $symb[1];
                }
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array($instruction_part[1]));
            }
            else
                exit(23);
            break;
        // <var> <symbol> <symbol>
        case "ADD":
        case "SUB":
        case "MUL":
        case "IDIV":
        case "LT":
        case "GT":
        case "EQ":
        case "AND":
        case "OR":
        case "STRI2INT":
        case "CONCAT":
        case "GETCHAR":
        case "SETCHAR":
            $arg_type[0] = "var";
            if($ip_count != 4)
            {
                exit(23);
            }
            else if(!is_var($instruction_part[1]))
            {
                exit(23);
            }
            else
            {
                if(is_symbol($instruction_part[2]))
                {
                    if(is_var($instruction_part[2]))
                    {
                        $arg_type[1] = "var";
                    }
                    else
                    {
                        $symb = explode("@", $instruction_part[2]);
                        $arg_type[1] = $symb[0];
                        $instruction_part[2] = $symb[1];
                    }
                }
                else
                {
                    exit(23);
                }
                if(is_symbol($instruction_part[3]))
                    {
                        if(is_var($instruction_part[3]))
                        {
                            $arg_type[2] = "var";
                        }
                        else
                        {
                            $symb = explode("@", $instruction_part[3]);
                            $arg_type[2] = $symb[0];
                            $instruction_part[3] = $symb[1];
                        }
                    }
                    else
                    {
                        exit(23);
                    }
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array($instruction_part[1], $instruction_part[2], $instruction_part[3]));
            }
            break;

        // <var> <symbol>
        case "MOVE":
        case "INT2CHAR":
        case "STRLEN":
        case "TYPE":
        case "NOT":
            $arg_type[0] = "var";
            if($ip_count != 3)
                exit(23);
            else if(!is_var($instruction_part[1]))
                exit(23);
            else
            {
                if(is_symbol($instruction_part[2]))
                {
                    if(is_var($instruction_part[2]))
                    {
                        $arg_type[1] = "var";
                    }
                    else
                    {
                        $symb = explode("@", $instruction_part[2]);
                        $arg_type[1] = $symb[0];
                        $instruction_part[2] = $symb[1];
                    }
                }
                else
                    exit(23);
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array($instruction_part[1], $instruction_part[2]));
            }
            break;
        
        // <var> <type>
        case "READ":
            $arg_type[0] = "var";
            $arg_type[1] = "type";
            if($ip_count != 3)
                exit(23);
            else if(!is_var($instruction_part[1]) || ! is_type($instruction_part[2]))
                exit(23);
            else
            {
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array($instruction_part[1], $instruction_part[2]));
            }
            break;

        // <label> <symbol> <symbol>
        case "JUMPIFEQ":
        case "JUMPIFNEQ":
            $arg_type[0] = "label";
            if($ip_count != 4)
                exit(23);
            else if(!is_label($instruction_part[1]))
                exit(23);
            else
            {if(is_symbol($instruction_part[2]))
                {
                    if(is_var($instruction_part[2]))
                    {
                        $arg_type[1] = "var";
                    }
                    else
                    {
                        $symb = explode("@", $instruction_part[2]);
                        $arg_type[1] = $symb[0];
                        $instruction_part[2] = $symb[1];
                    }
                }
                else
                    exit(23);
                if(is_symbol($instruction_part[3]))
                    {
                        if(is_var($instruction_part[3]))
                        {
                            $arg_type[2] = "var";
                        }
                        else
                        {
                            $symb = explode("@", $instruction_part[3]);
                            $arg_type[2] = $symb[0];
                            $instruction_part[3] = $symb[1];
                        }
                    }
                    else
                        exit(23);
                add_instruction($instruction_num, $instruction_part[0], $ip_count - 1, $arg_type, array($instruction_part[1], $instruction_part[2], $instruction_part[3]));
            }
            break;

        default:
            exit(22);
            break;
    }
}

$output = add_to_output($output, "</program>");
echo $output;
exit(0);

/*
    ADD TO OUTPUT
*/

function add_to_output($output, $new)
{
    return $output.$new."\n";
}

function add_instruction($count, $instruction, $arg_count, $arg_type, $args)
{
    $instruction = strtoupper($instruction);
    global $output;
    $output = add_to_output($output, "\t<instruction order =\"$count\" opcode=\"$instruction\">");
    switch($arg_count)
    {
        case 1:
            $output = add_to_output($output, "\t\t<arg1 type=\"$arg_type[0]\">$args[0]</arg1>");
            break;
        case 2:
            $output = add_to_output($output, "\t\t<arg1 type=\"$arg_type[0]\">$args[0]</arg1>");
            $output = add_to_output($output, "\t\t<arg2 type=\"$arg_type[1]\">$args[1]</arg2>");
            break;
        case 3:
            $output = add_to_output($output, "\t\t<arg1 type=\"$arg_type[0]\">$args[0]</arg1>");
            $output = add_to_output($output, "\t\t<arg2 type=\"$arg_type[1]\">$args[1]</arg2>");
            $output = add_to_output($output, "\t\t<arg3 type=\"$arg_type[2]\">$args[2]</arg3>");
            break;
    }
    $output = add_to_output($output,"\t</instruction>");
}

/*
    STRING MODIFYING FUNCTIONS
*/

function delete_comments($string)
{
    return preg_replace("/#.*/", '', $string);
}

function delete_whitespace($string)
{
    $pattern = '/[ \t]+/';
    $line = preg_replace($pattern, ' ', $string);
    $line = trim($line);
    return $line;
}

function process_line($line)
{
    $line = delete_comments($line);
    $line = trim($line);
    $line = delete_whitespace($line);
    $line = preg_replace("/&/",'&amp;',$line);                       
    $line = preg_replace("/</",'&lt;',$line);
    $line = preg_replace("/>/",'&gt;',$line);
    return $line;
}

/*
    SYNTAX CHECKS
*/

function is_var($string)
{
    if (preg_match("/^(LF|TF|GF)@([A-Za-z_\-$&;%*!?]([A-Za-z0-9_\-$&;%*!?])*)$/", $string))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

function is_label($string)
{
    if (preg_match("/^([A-Za-z_\-$&;%*!?]([A-Za-z0-9_\-$&;%*!?])*)$/", $string))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

function is_symbol($string)
{
    if (preg_match("/^(LF|TF|GF)@([_\-$#%*!?A-Za-z]([A-Za-z0-9_\-$#%*!?])*)$/", $string))
    {
        return 1;
    }
    if (preg_match("/^(bool)@(true|false)$/", $string))
    {
        return 1;
    }
    if (preg_match("/^(int)@[+-]?[0-9]+$/", $string))
    {
        return 1;
    }
    if (preg_match("/^nil@nil$/", $string))
    {
        return 1;
    }
    if (preg_match("/^string@(([^\\\]*)(\\\[0-9]{3})*)*$/", $string))
    {
        return 1;
    }
    return 0;
}

function is_type($string)
{
    if($string == "int")
        return 1;
    if($string == "bool")
        return 1;
    if($string == "string")
        return 1;
    return 0;
}

?>