if ! command -v convert &> /dev/null; then
    sudo pacman -Sy imagemagick
fi

rm -rf target
mkdir target
mkdir -p target/assets

for file in assets/*; do
    filename=$(basename "$file")
    filename="${filename%.*}"
    magick "$file" "target/assets/$filename.bmp"
done

if make all; then
./target/ParticleSim
fi