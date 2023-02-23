param(
    [Parameter()]
    [string]$path
)

class FData
{
    [Collections.Generic.List[string]]$classes
    [string]$namespace

    FData()
    {
        $this.classes = New-Object Collections.Generic.List[string]
    }
}

$allDatas = New-Object Collections.Generic.List[FData]

function GetIndex
{
    param([string]$namespace)
    for ($i = 0; $i -lt $allDatas.Count; $i = $i + 1)
    {
        if ($allDatas[$i].namespace -eq $namespace)
        {
            return $i
        }
    }
    return -1
}

function IsUClass
{
    param([Collections.ArrayList] $fileContents)
    for ($i = 0; $i -lt $fileContents.Count; $i = $i + 1)
    {
        if ($fileContents[$i].Contains("UCLASS") -and $fileContents[$i] -notmatch "UCLASS(...)")
        {
            return $true
        }
    }
    return $false
}

function IsForwardedNamespace
{
    param([Collections.ArrayList]$contents, [Int16]$index)
    $parenthesisCount = 0
    for ($i = $index + 1; $i -lt $contents.Count; $i = $i + 1)
    {
        $line = $contents[$i]
        if ($line.Contains("{"))
        {
            $parenthesisCount = $parenthesisCount + 1
        }
        if ($line.Contains("}"))
        {
            $parenthesisCount = $parenthesisCount - 1
        }
        if ($line.Contains("UCLASS()"))
        {
            return $false
        }
        if ($parenthesisCount -eq 0)
        {
            return $true
        }
    }
    return $false
}

function Exist
{
    param([string]$namespace)
    for ($i = 0; $i -lt $allDatas.Count; $i = $i + 1)
    {
        if ($allDatas[$i].namespace -eq $namespace)
        {
            return $true
        }
    }
    return $false
}

function GetAllNamespaces
{
    param([Collections.Generic.List[string]] $allUClass)

    for ($x = 0; $x -lt $allUClass.Count; $x = $x + 1)
    {
        $fullPath = $allUClass[$x]
        $className = (Get-Item $fullPath).BaseName
        $fileContents = (Get-Content -Path $fullPath) -as [Collections.ArrayList]
        $currentNamespace = ""
        for ($i = 0; $i -lt $fileContents.Count; $i = $i + 1)
        {
            $line = $fileContents[$i]
            if ( $line.Contains("namespace"))
            {
                $isFowarded = IsForwardedNamespace -contents $fileContents -index $i
                if (-not$isFowarded)
                {
                    $namespace = $line.Replace("namespace", "").Trim()

                    if ( [string]::IsNullOrEmpty($currentNamespace))
                    {
                        $currentNamespace = $namespace
                    }
                    else
                    {
                        $currentNamespace += "::$namespace"
                    }
                }
            }
        }
        if (-not [string]::IsNullOrEmpty($currentNamespace))
        {
            if (-not(Exist -namespace $currentNamespace))
            {
                $data = [FData]::new()
                $data.namespace = $currentNamespace
                $data.classes.Add($fullPath)
                $allDatas.Add($data)
            }
            else
            {
                $index = GetIndex -namespace $currentNamespace
                $allDatas[$index].classes.Add($fullPath)
            }
        }
    }
}

function GetAllUClass
{
    $uclass = New-Object Collections.Generic.List[string]
    Get-ChildItem $path -Recurse -Filter *.h |
            ForEach-Object {
                $fullPath = $_.FullName
                $fileContents = (Get-Content -Path $fullPath) -as [Collections.ArrayList]
                if (IsUClass -fileContents $fileContents)
                {
                    $uclass.Add($fullPath)
                }
            }
    return $uclass
}

function CreateFile
{
    $assemblyPath = "$path/Assembly.h"
    $result = "#pragma once`n"
    $result += "#include `"Engine/Utils/ObjectMacro.h`"`n`n"
    foreach ($h in $allDatas)
    {
        $namespace = $h.namespace
        $result += "using namespace $namespace;`n`n"
        $classes = $h.classes
        for ($i = 0; $i -lt $classes.Count; $i = $i + 1)
        {
            $includePath = $classes[$i].Replace($path, "").TrimStart()
            $className = $includePath.SubString($includePath.LastIndexOf('\') + 1)
            $className = $className.Replace(".h", "").TrimEnd()
            $result += "#include `"$includePath`"`n"
            $result += "REGISTER_TYPE($className)`n"
        }
    }
    Set-Content -Path $assemblyPath -Value $result
}

$allUClass = GetAllUClass
GetAllNamespaces -allUClass $allUClass

CreateFile
