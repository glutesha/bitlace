<script lang="ts">
    import { pics, pushSaves } from "../saves";

	async function onFileChange(event: Event) {
		const input = event.target as HTMLInputElement;
		const file = input.files?.[0];
		if (!file) return;

		const reader = new FileReader();
		reader.onload = async () => {
			try {
				const data = JSON.parse(reader.result as string);;
                const saves: Array<Array<Array<boolean>>> = data;
                pics.set(saves);
                await pushSaves();
			} catch (err) {
				console.error("Error loading file:", err);
			}
		};
        reader.readAsText(file);
	}

</script>

<label class="bg-neutral-800 hover:bg-neutral-900 active:bg-neutral-950 rounded-3xl size-xl text-white px-5 py-3 text-3xl text-center font-bold flex-1" for="file">
    Import
	<input 
        id="file"
		type="file" 
		accept=".json" 
		on:change={onFileChange} 
		class="hidden"
	/>
</label>
