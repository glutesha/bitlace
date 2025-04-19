echo "Building front-end..."
cd front
npm install
npm run build
cd ..
echo "Copying front/dist to data"
rm -rf data
mkdir -p data
cp -a front/dist data/
echo "Done!"