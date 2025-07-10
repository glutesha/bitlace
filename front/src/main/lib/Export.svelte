<script lang="ts">
    import { pics } from "../saves";
    function onClick(){
        const saves = JSON.stringify($pics);

        const blob = new Blob([saves], { type: "application/json" });
        const url = URL.createObjectURL(blob);

        const a = document.createElement("a");
        a.href = url;
        a.download = "saves.json"; 
        a.click();
    }
</script>

<button on:click={onClick} class="bg-neutral-800 hover:bg-neutral-900 active:bg-neutral-950 rounded-3xl size-xl text-white px-5 py-3 text-3xl font-bold flex-1">Export</button>