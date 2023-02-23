param(
    [Parameter()]
    [String]$path
)

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

Get-ChildItem $path -Recurse -Filter *.h |
        ForEach-Object {
            $scriptPath = $_.FullName
            $className = (Get-Item $scriptPath).BaseName
            $fileContents = Get-Content -Path $scriptPath
            $isPublic = $false
            $isObject = $false
            $flags = ""
            $indexFile = 0

            if ($className -eq "Object")
            {
                return
            }

            for ($i = 0; $i -lt $fileContents.Count; $i = $i + 1)
            {
                $line = $fileContents[$i]

                if ($line -match "UCLASS\(\)")
                {
                    $isObject = $true
                }

                if ($isObject -eq $false)
                {
                    continue
                }

                if ( [string]::IsNullOrEmpty($line))
                {
                    continue
                }

                $isPublic = IsPublic -line $line -result $isPublic

                if ($line -match "UPROPERTY\(\)")
                {
                    $flags = ""
                    if ($isPublic)
                    {
                        $flags = AddFlag -currentFlag $flags -newFlag "Public"
                    }
                    else
                    {
                        $flags = AddFlag -currentFlag $flags -newFlag "NoPublic"
                    }
                    if ( $line.Contains("static"))
                    {
                        $flags = AddFlag -currentFlag $flags -newFlag "Static"
                    }

                    $isPointer = $line.Contains("*")
                    $field = ReplaceStr -str $line -toReplace @("inline", "const", "static", "constexpr", "UPROPERTY()") -to ""
                    $field = $field.TrimStart()
                    if ( $field.Contains(">"))
                    {
                        $str = $field.SubString($field.IndexOf(">"), $field.IndexOf("="))
                        $isPointer = $str.Contains("*")
                    }
                    $field = $field.Substring($field.IndexOf(' ') + 1)
                    $field = $field.Substring(0,$field.IndexOf(' ')).Trim()
                    $result = ""
                    if ($isPointer)
                    {
                        $result = "REGISTER_FIELD($field, $field, $flags)"
                    }
                    else
                    {
                        $result = "REGISTER_FIELD($field, &$field, $flags)"
                    }
                    $file = (Get-Content $scriptPath) -as [Collections.ArrayList]
                    if ($fileContents[$i + 1] -match "REGISTER_FIELD")
                    {
                        $file.Remove($fileContents[$i + 1])
                        $file.Insert($i + 1, $result)
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
            for ($i = 0; $i -lt $fileContents.Count; $i = $i + 1)
            {
                $line = $fileContents[$i]
                if ($line -match "REGISTER_FIELD" -and $fileContents[$i - 1] -notmatch "UPROPERTY")
                {
                    $file = (Get-Content $scriptPath) -as [Collections.ArrayList]
                    $file.RemoveAt($i - $index)
                    $index = $index + 1
                    $file | Set-Content $scriptPath
                }
            }
        }
