param(
    [Parameter()]
    [string]$path
)

function ReplaceStr
{
    param([string]$str, [string[]]$toReplace, [string]$to)
    $count = $toReplace.Count
    for ($i = 0; $i -lt $toReplace.Count; $i = $i + 1)
    {
        $str = $str.Replace($toReplace[$i], $to)
    }
    return $str
}

function IsPublic
{
    param([string]$line, [boolean]$result)
    if ( $line.Contains("public:"))
    {
        return $true
    }
    elseif ($line.Contains("private:") -or $line.Contains("protected:"))
    {
        return $false
    }
    return $result
}

function AddFlag
{
    param([string]$currentFlag, [string]$newFlag)
    if ( $currentFlag.Contains($newFlag))
    {
        return $currentFlag
    }
    if ( [string]::IsNullOrEmpty($currentFlag))
    {
        return "BindingFlags::$newFlag"
    }
    return "$currentFlag | BindingFlags::$newFlag"
}

Get-ChildItem $path -Recurse -Filter *.h |
        ForEach-Object {
            $scriptPath = $_.FullName
            $className = (Get-Item $scriptPath).BaseName
            $filecontents = Get-Content -Path $scriptPath
            $isObject = $false
            $isPublic = $false
            $isStatic = $false
            $flags = ""
            $indexFile = 0

            if ($className -eq "Object")
            {
                return
            }
            
            for ($i = 0; $i -lt $filecontents.Count; $i = $i + 1)
            {
                $flags = ""
                $line = $filecontents[$i]

                if ( [string]::IsNullOrEmpty($line))
                {
                    continue
                }
                
                if ($line -match "UCLASS\(\)")
                {
                    $isObject = $true
                }

                if ($isObject -eq $false)
                {
                    continue
                }
                
                $isPublic = IsPublic -line $line -result $isPublic
                if ($line -match "UFUNCTION\(\)")
                {
                    $isStatic = $line.Contains("static")
                    $function = ReplaceStr -str $line -toReplace @("UFUNCTION()", "static", "const", "inline") -to ""
                    $function = $function.TrimStart()

                    $startIndex = $function.IndexOf(' ') + 1
                    $functionName = $function.SubString($startIndex, $function.IndexOf('(') - $startIndex)

                    $startIndex = $function.IndexOf('(') + 1
                    $parameters = $function.SubString($startIndex, $function.IndexOf(')') - $startIndex)

                    $result = "REGISTER_METHOD($functionName, &$className::$functionName, "
                    if ( [string]::IsNullOrEmpty($parameters.Trim()))
                    {
                        $result += "{}, "
                    }
                    else
                    {
                        $result += "(std::vector<Engine::Reflection::ParameterInfo*>{"
                        # assign parameters
                        $splitedParameters = $parameters.Split(',')
                        for ($j = 0; $j -lt $splitedParameters.Count; $j = $j + 1)
                        {
                            $param = $splitedParameters[$j].TrimStart()
                            $parameterName = ReplaceStr -str $parameterName -toReplace @("const", "*", "&") -to ""
                            $parameterName = $param.SubString($param.LastIndexOf(' ') + 1).Trim()
                            $result += "new Engine::Reflection::ParameterInfo(`"$parameterName`", $j)"
                            if ($j -lt $splitedParameters.Count - 1)
                            {
                                $result += ","
                            }

                        }

                        $result += "}), "
                    }
                    if ($isPublic)
                    {
                        $flags = AddFlag -currentFlag $flags -newFlag "Public"
                    }
                    else
                    {
                        $flags = AddFlag -currentFlag $flags -newFlag "NoPublic"
                    }
                    if ($isStatic)
                    {
                        $flags = AddFlag -currentFlag $flags -newFlag "Static"
                    }
                    $result += "$flags)"

                    $file = (Get-Content $scriptPath) -as [Collections.ArrayList]
                    if ($filecontents[$i + 1] -match "REGISTER_METHOD")
                    {
                        $file.Remove($filecontents[$i + 1])
                        $file.Insert($i + 1, $result)
                        $indexFile = $indexFile - 1
                    }
                    else
                    {
                        $file.Insert($i + $indexFile + 1, $result)
                        $indexFile = $indexFile + 1
                    }
                    $file | Set-Content $scriptPath
                }
            }

            $index = 0
            for ($i = 0; $i -lt $filecontents.Count; $i = $i + 1)
            {
                $line = $filecontents[$i]
                if ($line -match "REGISTER_METHOD" -and $filecontents[$i - 1] -notmatch "UFUNCTION")
                {
                    $file = (Get-Content $scriptPath) -as [Collections.ArrayList]
                    $file.RemoveAt($i - $index)
                    $index = $index + 1
                    $file | Set-Content $scriptPath
                }
            }
        }