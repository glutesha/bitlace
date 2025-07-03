<script lang="ts">
    import Preview from "./Preview.svelte";
    import { pics, fetchSaves } from "../saves";
    import { onMount } from "svelte";


    onMount(async () => {
        await fetchSaves();
    })
</script>

<div class="bg-neutral-900 rounded-2xl mt-3 mb-2 p-4 gap-2 w-full min-h-95 shadow-xl shadow-black/50 flex justify-center flex-wrap max-w-[380px]">
  {#each $pics as pic, id}
    <Preview id={id} display={pic} />
  {/each}
</div>