echo "Building front-end..."
cd front
npm install
npm run build
cd ..
echo "Copying front/dist to data"
rm -rf data/dist
mkdir -p data/dist
cp -a front/dist data/
echo "Done!"